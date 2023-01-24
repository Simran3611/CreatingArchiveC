This is the beginning of the README file

There are 4 parts implemented in the program. This program is supposed to resemble an archive setup in C on the shell

In order to begin first, compile the program using "make"

The first being the creation of the filesystem and the adding of a certain file into the file system
In order to run this, try the following command...
./filefs -a /a/b/c -f example

The second part would be the listing of all the files in the filesystem.
I have implemented this part. However in stead of recursion, I have used '->' to show the path in a certain filesystem requested
In order to run this, try the following command...
./filefs -l -f example

The third part involves the removing of a certain file within the filesystem.
The program will take the pathname of the file requested in order to remove. If that pathname does exist then the file would be removed
In order to check this you would need to do the listing of the files in the filesystem
In order to run this, try the following command...
./filefs -r /a/b/c -f example

The last part is the redirection. Where the contents of one file would be redirected to the other file requested
In order for this to work, you would need to have certain contents written in the file which would be redirected
In order to run this, try the following command...
./filefs -e /a/b/c -f example > foobar
