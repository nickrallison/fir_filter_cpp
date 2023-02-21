if [ ! -d "libs/AudioFile" ]; then 
    cd libs
    git submodule add https://github.com/adamstark/AudioFile.git
    cd ..
fi

if [ ! -d "assets/downloads" ]; then 
    cd assets
    mkdir downloads
    cd downloads
    curl https://www.voiptroubleshooter.com/open_speech/american/OSR_us_000_0010_8k.wav -o OSR_us_000_0010_8k.wav
    cd ../..
fi