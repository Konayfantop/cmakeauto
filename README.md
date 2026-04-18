Warnings : https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
Optimize : https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

-> there is no stable contract , so the way we deal with it must be 
1) we go step by step behind /a/b/c -> /a/b/ -> /a/ , etc. if we find in the dir path the .automake folder then we know it's a root dir of the repo/project.
2) if not we have to drop a warning and we consider the path we are currently on to give in