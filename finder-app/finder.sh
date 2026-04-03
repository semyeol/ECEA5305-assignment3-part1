# Accepts the following runtime arguments: the first argument is a path to a directory on the filesystem, referred to below as filesdir; 
# the second argument is a text string which will be searched within these files, referred to below as searchstr

# Exits with return value 1 error and print statements if any of the parameters above were not specified

# Exits with return value 1 error and print statements if filesdir does not represent a directory on the filesystem

# Prints a message "The number of files are X and the number of matching lines are Y" where X is the number of files in the directory and 
# all subdirectories and Y is the number of matching lines found in respective files, where a matching line refers to a line which contains 
# searchstr (and may also contain additional content).

#!/bin/sh

filesdir=$1
searchstr=$2

# if either of the parameters are missing
# '-o' is OR
# '-z' checks if variable is empty
if [ -z "$filesdir" -o -z "$searchstr" ]
then 
    echo "One or both of the parameters are empty"
    exit 1
fi

# '-d' checks if it's a directory
if [ ! -d "$filesdir" ]
then 
    echo "Directory is not valid"
    exit 1
fi

# '$()' runs the command and captures its output
# 'find' prints out each file path, one per line
# '-type f' means files only, not directories
# 'wc -l' counts the lines after 'find' runs completely
# '|' the output of the command is the input of the next
X=$(find "$filesdir" -type f | wc -l)


# grep into all files recursively and increment Y for each match
Y=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"