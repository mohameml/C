#!/usr/bin/perl

(@ARGV == 1) || 
    die "please provide the name of the solvemaze binary to test\n" ;

my $bin = $ARGV[0];

(-f $bin) || die "binary $bin not found\n" ;

my @testFiles = ("laby_ko_0D.txt","laby_ko_2A.txt","laby_ko_2D.txt",
		 "laby_ko_badChar.txt","laby_ko_longLine1.txt",
		 "laby_ko_longLine2.txt","laby_ko_missingNL.txt");

foreach my $t (@testFiles) {
    print "Test: $t\n\n";
    system("$bin $t\n") ;
    print "\n\nHit RETURN for next test:\n" ;
    <STDIN>;
}
