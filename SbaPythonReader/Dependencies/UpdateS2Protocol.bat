@echo off
REM Updates s2protocol to the latest commit on it's master branch
REM This assumes that s2protocol is in the path.
REM Note: This will remove your old s2protocol folder overwriting any changes!
REM You must run this from the Dependencies folder or it will create s2protocol in whatever directory you happen to run from.

REM Clone the repo
mkdir temp
cd temp
git clone https://github.com/Blizzard/s2protocol.git

REM Add a file with the commit in it for tracking the current version
cd s2protocol/s2protocol
git rev-parse HEAD > LastCommit.txt
cd ../../../

REM Remove the old one
rmdir /S /Q s2protocol

REM Copy the new one
echo D|xcopy /E "temp/s2protocol/s2protocol" "s2protocol"

REM Copy the license
copy /Y "temp\s2protocol\LICENSE" "s2protocol\LICENSE"

REM Delete the temp directory
rmdir /S /Q temp

echo Done
