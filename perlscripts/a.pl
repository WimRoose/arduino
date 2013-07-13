#!/usr/bin/perl
use warnings;
use strict;

my $test;
my $moist_val;
my $update_rrd;
my $light_val;

#open(MYOUTFILE, ">", "/home/lou/arduino.log") || die "Couldn't open file file.txt, $!";
# Set up the serial port
    use Device::SerialPort;
    my $port = Device::SerialPort->new("/dev/ttyACM0");
     
    # 19200, 81N on the USB ftdi driver
    $port->baudrate(9600); # you may change this value
    $port->databits(8); # but not this and the two following
    $port->parity("none");
    $port->stopbits(1);
    $port->read_const_time(500);
    $port->read_char_time(500);
    #$port->are_match("\n");

my $loop=1;

# heel belangrijk: bij het printen in de loop steeds een newline toevoegen achteraan
# anders blijft het gebufferd

while ($loop == 1) {

	my $lees_commando = `cat /home/lou/commando`;
	my $clear_commando;
	chomp($lees_commando);
	if ($lees_commando ne "")	{
		print "Received " . $lees_commando . ", sending to arduino...\n";		
		my $count_out = $port->write($lees_commando);
		$clear_commando = `echo "" > /home/lou/commando`;
	}
	my $char = $port->read(3);
	
	if ($char) {

	print "Received " . $char . " from Arduino\n";
		

	}  
#close(MYOUTFILE);

}
