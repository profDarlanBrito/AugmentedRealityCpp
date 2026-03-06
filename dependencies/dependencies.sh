sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install bison
if [ -d "$HOME/vcpkg" ]; then
  echo "vcpkg directory already exists, skipping clone."
else
  git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
  cd ~/vcpkg
  ./bootstrap-vcpkg.sh
  ./vcpkg integrate install
  export VCPKG_ROOT=~/vcpkg
fi
sudo apt install libx11-dev libxft-dev libxext-dev
sudo apt-get install libxi-dev libxtst-dev
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libgl1-mesa-glx
sudo apt-get install libgl1-mesa-dri
sudo apt-get install libx11-xcb-dev
sudo apt-get install libxcb-dri3-dev
sudo apt-get install x11-xserver-utils
sudo apt-get install libxrandr-dev