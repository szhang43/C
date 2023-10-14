#!/usr/bin/env bash

# Donations (2022) checker script.
# Adapted by: S. Isaac Geronimo Anderson (Fall 2022)

correctOutput="3C-correct-output.txt"
testInput="3C-input.txt"
projectSubmission="proj3C.c"
projectBinary="proj3C"
trickyInput="${testInput}.$$"
submissionOutput="your-output.txt"
tabFreeOutput="tab-free-${submissionOutput}.$$"

if [ ! -f "${correctOutput}" ]; then
   echo "Error: You must download the file ${correctOutput} and place it in this directory."
   echo "Exiting."
   exit 1
fi

if [ ! -f "${testInput}" ]; then
   echo "Error: You must download the file ${testInput} and place it in this directory."
   echo "Exiting."
   exit 1
fi

if [ ! -f "${projectSubmission}" ]; then
   echo "Error: You must place the file ${projectSubmission} in the current directory."
   echo "Exiting."
   exit 1
fi

gcc -o "${projectBinary}" "${projectSubmission}"
if [ $? != 0 ]; then
   echo "Error: Your submission failed to compile."
   exit 1
fi

mv "${testInput}" "${trickyInput}"
eval "./${projectBinary} ${trickyInput} > ${submissionOutput}"
mv "${trickyInput}" "${testInput}"

# Checking for correct output.
diff "${submissionOutput}" "${correctOutput}"
if [ $? != 0 ]; then
   sed "s/      //g" "${submissionOutput}" > "${tabFreeOutput}"
   diff "${tabFreeOutput}" "${correctOutput}"
   if [ $? != 0 ] ; then
      rm "${tabFreeOutput}"
      echo "Error: Your output does not match correct output."
      exit 1
   fi
   rm "${tabFreeOutput}"
fi

echo "\
Your program appears to be working correctly:
It compiles, runs, and generates the correct output.
Please upload your code to Canvas, following the prompt instructions.
Grading will comprise the steps performed by this script,
complemented by inspecting your code."

# End.
