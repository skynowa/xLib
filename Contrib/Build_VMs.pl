#!/usr/bin/perl -w

##############################################################################################################
# File name:   Build_VMs.pl
# Description: build xLib on virtual PCs via SSH
#
##############################################################################################################


use strict;
use Net::OpenSSH;
    # v0.52, http://search.cpan.org/~salva/Net-OpenSSH-0.52/lib/Net/OpenSSH.pm
    # Install: sudo cpanm -n Net::OpenSSH


##############################################################################################################
# target tasks
my @aHosts = (
    ##########################################################################################################
    # Host           | Login | Password | Build commands                                                     # 
    ##########################################################################################################

    ['192.168.1.31', 'root', 'master', 'cd /root/scripts/xLib      && ./Tests_FreeBSD.sh && ./Lib_FreeBSD.sh'],
    ['192.168.1.32', 'root', 'master', 'cd /root/scripts/xLib      && ./Tests_FreeBSD.sh && ./Lib_FreeBSD.sh'],
    ['192.168.1.33', 'root', 'master', 'cd /root/scripts/xLib      && ./Tests_FreeBSD.sh && ./Lib_FreeBSD.sh'],
    ['192.168.1.34', 'root', 'master', 'cd /root/scripts/xLib      && ./Tests_FreeBSD.sh && ./Lib_FreeBSD.sh'],
    ['192.168.1.35', 'root', 'master', 'cd /root/scripts/xLib      && ./Tests_FreeBSD.sh && ./Lib_FreeBSD.sh'],
    ['192.168.1.36', 'root', 'master', 'cd /root/scripts/xLib      && ./Tests_FreeBSD.sh && ./Lib_FreeBSD.sh'],
    ['192.168.1.40', 'igor', 'master', 'cd /home/igor/scripts/xLib && ./Tests_Linux.sh   && ./Lib_Linux.sh  '],
    ['192.168.1.41', 'igor', 'master', 'cd /home/igor/scripts/xLib && ./Tests_Linux.sh   && ./Lib_Linux.sh  ']
); 

# console colors
my $COLOR_RESET  = "\e[0;37;40m";
my $COLOR_BLACK  = "\e[22;30m";
my $COLOR_RED    = "\e[22;91m";
my $COLOR_GREEN  = "\e[22;32m";
my $COLOR_YELLOW = "\e[22;93m";

my @aChildsPids; 

##############################################################################################################
# start
print `clear`;
print `clear`;
print "\nStart...\n\n"; 

for (my $i = 0; $i <= $#aHosts; $i ++) { 
    my $pid = fork(); 
    if ($pid) { 
        # it's parent 
        push(@aChildsPids, $pid); 
    } 
    elsif (0 == $pid) { 
        # it's child
        iWorkFunc($i); 

        exit 0; 
    } 
    else { 
        die "Fork fail: $!\n"; 
    } 
} 

# sleep(2);
# print "\nWork...\n\n"; 

# collect child pids
foreach (@aChildsPids) { 
    my $pid = waitpid($_, 0); 
    # print "Done machine $pid\n";
} 
  
print "\nDone all.\n\n"; 


##############################################################################################################
# work function for process
sub iWorkFunc {
    my @Params             = @_; 
    my $iIndex             = $Params[0];

    my $sHost              = $aHosts[$iIndex][0];
    my $sUser              = $aHosts[$iIndex][1];
    my $sPassword          = $aHosts[$iIndex][2];
    my $sCmdBuild          = $aHosts[$iIndex][3];
    my $iConnectionTimeout = 1000;

    print "Task: $sHost, $sUser, $sPassword, $sCmdBuild\n";

    # build target
    {
        my $ssh = Net::OpenSSH->new(
                        $sHost, 
                        user     => $sUser, 
                        password => $sPassword, 
                        timeout  => $iConnectionTimeout);
        if ($ssh->error) {
            die $ssh->error;
        }
 
        my ($sStdOut, $sStdError) = $ssh->capture2($sCmdBuild);
        if ($ssh->error) {
            die $ssh->error;
        }
        # print "\n\nstdout>>>\n    $sStdOut    \n<<<\n\n";
        # print "\n\nstderr>>>\n    $sStdError  \n<<<\n\n";

        my $sError = '';

        if ("" eq $sStdError) {
            $sError = 'OK';
        } else {
            $sError = $sStdError;
        }

        print "$COLOR_YELLOW Host $aHosts[$iIndex][0] $COLOR_RESET >>> $COLOR_RED $sError $COLOR_RESET\n";
    }

    return 1;
} 
##############################################################################################################
