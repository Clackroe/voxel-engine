#!/bin/bash



PrintHelp() {
  echo
  echo "Enter 'build.sh action' where action is one of the following:"
  echo
  echo "   clean             Remove all binaries, intermediate binaries, and project files."
  echo "   codelite          Generate CodeLite project files."
  echo "   gmake             Generate GNU makefiles for Linux."
  echo "   gmake2            Generate alternate GNU makefiles for Linux."
  echo "   vs2005            Generate Visual Studio 2005 project files."
  echo "   vs2008            Generate Visual Studio 2008 project files."
  echo "   vs2010            Generate Visual Studio 2010 project files."
  echo "   vs2012            Generate Visual Studio 2012 project files."
  echo "   vs2013            Generate Visual Studio 2013 project files."
  echo "   vs2015            Generate Visual Studio 2015 project files."
  echo "   vs2017            Generate Visual Studio 2017 project files."
  echo "   vs2019            Generate Visual Studio 2019 project files."
  echo "   vs2022            Generate Visual Studio 2022 project files."
  echo "   xcode4            Generate Apple Xcode 4 project files."
  Done
}


Done() {
  # Done with the script.
  exit 0
}

if [ -z "$1" ]; then
  PrintHelp
else
  vendor/premake5 $1
  Done
fi

# Check for the action and perform accordingly
if [ "$1" == "compile" ]; then
  echo "Compiling..."
else
  vendor/premake5 "$1"
  Done
fi
