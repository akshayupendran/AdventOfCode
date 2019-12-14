#define _GNU_SOURCE 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

static int do_debug = -1;
void debug(const char *fmt, ...) {
  va_list ap;
  if (do_debug < 0)
    do_debug = !!getenv("DEBUG");
  if (do_debug > 0) {
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
  }
}

#define LIMIT 1000
#define MAXIN 8

struct react {
  char out[6];
  int produce;
  long long avail;
  int n_in;
  struct {
    char in[6];
    int consume;
    int idx;
  } in[MAXIN];
};
struct react list[LIMIT] = { { .out = "ORE", .produce = 1,
			       .avail = 1000000000000LL, }, };
static int count;
static int fuel_idx;
static long long produced;

static int __attribute__((noreturn))
die(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  putchar('\n');
  exit(1);
}

static int
find(const char *name, int *idx) {
  int i;

  if (*idx >= 0)
    return *idx;
  for (i = 0; i <= count; i++)
    if (!strcmp(list[i].out, name))
      return *idx = i;
  die("missing rule for %s", name);
}

static bool
produce(int idx, long long amt) {
  int i;
  long long need = amt - list[idx].avail;
  long long mult = need > 0 ? (need + list[idx].produce
			       - 1) / list[idx].produce : 0;

  debug("want %lld of %s, have %lld, needs %lld more batches\n", amt,
	list[idx].out, list[idx].avail, mult);
  if (!idx && need > 0)
    return false;
  for (i = 0; i < list[idx].n_in; i++)
    if (!produce(find(list[idx].in[i].in, &list[idx].in[i].idx),
		 mult * list[idx].in[i].consume))
      return false;
  list[idx].avail += mult * list[idx].produce - amt;
  if (idx == fuel_idx)
    produced += amt;
  return true;
}

int main(int argc, char **argv) {
  int ch, i;
  long long min;

  if (argc > 1)
    if (!(stdin = freopen(argv[1], "r", stdin))) {
      perror("failure");
      exit(2);
    }

  while ((ch = getchar()) != EOF) {
    count++;
    if (count >= LIMIT)
      die("recompile with larger LIMIT");
    ungetc(ch, stdin);
    i = 0;
    do {
      if (scanf(" %d %5[A-Z]", &list[count].in[i].consume,
		list[count].in[i].in) != 2)
	die("parse failure at line %d", count - 1);
      list[count].in[i].idx = -1;
      if (i++ >= MAXIN)
	die("recompile with larger MAXIN");
    } while (getchar() != ' ');
    list[count].n_in = i;
    if (scanf("=> %d %5[A-Z]\n", &list[count].produce, list[count].out) != 2)
      die("parse failure at line %d", count - 1);
    if (!strcmp(list[count].out, "FUEL"))
      fuel_idx = count;
    debug("parsed instructions for %d %s from %d inputs\n",
	  list[count].produce, list[count].out, list[count].n_in);
  }
  printf("scanned %d formulas, fuel at line %d\n", count, fuel_idx - 1);

  if (!produce(fuel_idx, 1))
    die("unable to produce 1 fuel");
  min = 1000000000000LL - list[0].avail;
  printf("1 fuel requires %lld ore\n", min);
  while (list[0].avail > min) {
    printf("producing %lld more...\n", list[0].avail / min);
    if (!produce(fuel_idx, list[0].avail / min))
      die("unexpected failure in bulk production");
  }
  while (produce(fuel_idx, 1))
    printf("at %lld, used up spares for 1 more...\n", produced);
  printf("produced %lld total\n", produced);
  return 0;
}
