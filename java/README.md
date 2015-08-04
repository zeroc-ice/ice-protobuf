# Java Demo and Test

## Overview

This directory contains Java sample programs for using Ice with Protobuf.

## Build Instructions

### Prerequisites

If you've installed Ice in a non-standard location, you'll need to set the
`ICE_HOME` environment variable with the path name of the
installation directory. For example, on Linux or OS X:

    $ export ICE_HOME=~/testing/Ice

On Windows:

    > set ICE_HOME=C:\Ice

### Building

The build system for the Java sample programs uses [Gradle](http://gradle.org)
and includes a wrapper script or batch file that automatically downloads Gradle
and all other required components.

To build the demos, open a command window and run:

    gradlew build
