#!/usr/bin/perl
my @input = qw/0 0 0 0 0 1 1 1 1 1/;
sub count_zeros {
	my @input = @{$_[0]};
	binary_search( \@input, 0, (scalar @input) - 1 );
}
sub binary_search {
	my @haystack = @{$_[0]};
	my $begin = $_[1];
	my $end = $_[2];
	return -1 if ( $begin >= $end );
	my $current_position = int( ($begin + $end) / 2 );
	if( ($end - $begin) == 1 ) {
		return $begin if( $haystack[$begin] == 1 );
		return $end if( $haystack[$end] == 1 );
	} else {
		if( $haystack[$current_position] == 1 ) {
			return binary_search( \@input, $begin, $current_position );
		} else {
			return binary_search( \@input, $current_position, $end );
		}
	}
}
my $num_zeros = count_zeros( \@input );
if( $num_zeros == 5 ) {
	print "PASSED\n";
} else {
	print "$num_zeros : FAILED\n";
}

