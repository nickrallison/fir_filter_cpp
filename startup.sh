if [ ! -d "libs/AudioFile" ]; then 
    mkdir AudioFile
    git submodule add https://github.com/adamstark/AudioFile.git libs/AudioFile
fi
