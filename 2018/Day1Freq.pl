#!/usr/bin/perl
use strict;
use warnings;

my $number = 0;
my $number_t = 0;
my $i=o;
# First create the email message
open(FILE, "Day1FreqInput.txt");
while (<FILE>)
{
    chomp;
    ($number[$i]) = split("\t");
    $i =$i + 1
    #Sum All Frequencies
    $number_t = $number_t + $number[i];
    #Parse list and check if sum there
    while()
}
print "NUMBER: $number_t\n";
close(FILE);
exit();    
