#!/usr/bin/perl -w
use Cwd;

my $dir_to_process = getdcwd('C:');

opendir DH, $dir_to_process or die "Cannot open $dir_to_process: $!";

foreach $file (readdir DH) {
      
      $_ = "\"$file\"";
      
                     
     if(/(^[1-9])*.pdb/)
      {
            print "Processing pdb file $_!\n";            
            system "Surface_area_per_residue_2.exe", "$_"; 
      }
      
      
      if(/.dssp/)
      {
         if(/.exe/)
         {
         }
         else
         {
            print "Processing dssp file $_!\n";            
            system "Surface_areas_per_residue_1.exe", "$_";
         }            
      }
}
          
closedir DH;
