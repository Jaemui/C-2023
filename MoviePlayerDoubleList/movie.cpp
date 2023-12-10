#include <fstream>
#include <iostream>
#include <sstream>
#include "movie.h"

MoviePlayer::MoviePlayer(std::string filmName)
{
    currFrameNum = 0;
    mFilmName = filmName;
    loadTape();
    pos = mFilm.begin();
}

MoviePlayer::~MoviePlayer()
{
    mFilm.clear();
    pos = nullptr;
}

void MoviePlayer::clear(){
    mFilm.clear();
    pos = nullptr;
}

void MoviePlayer::goFwrd()
{
    if (currFrameNum < getNumFrames()){
        currFrameNum++;
        //moves the pointer forward
        if (pos != mFilm.end()){
            ++pos;
        }
        else{
            return;
        }
        
    }
    else{
        return;
    }
}

void MoviePlayer::goBack()
{
    //moves pointer backwards
    if (currFrameNum > 0){
        currFrameNum--;
        if (pos != mFilm.begin()){
            --pos;
        }
        else{
            return;
        }
    }
    else{
        return;
    }
}

void MoviePlayer::rewind()
{
    currFrameNum = 0;
    pos = mFilm.begin();
}

std::string MoviePlayer::getCurrFrame()
{
    if (pos != mFilm.end()){
        return *pos;
    }
    else{
        return "end of movie";
    }
}

void MoviePlayer::delCurrFrame()
{
    pos = mFilm.erase(pos);
    currFrameNum--;
}

void MoviePlayer::copyCurrFrame()
{
    std::string copyFrame = *pos;
    mFilm.insert(pos, copyFrame);
    currFrameNum++;
}


unsigned MoviePlayer::getCurrFrameNum() const
{
    return currFrameNum;;
}

unsigned int MoviePlayer::getNumFrames() const
{
    return mFilm.size();
}

unsigned int MoviePlayer::getFrameSize() const
{
    return FRAMESIZE;
}

void MoviePlayer::loadTape()
{
    mFilm.clear();
    int frameCount = 0;
    std::ifstream fileInput(mFilmName);
    std::string line;
    std::string frame;
    if (!fileInput.is_open()){ //checks if file is open
        std::cout << "Unable to load \"" << mFilmName << "\"!";
    }
    
    if (fileInput.is_open()){
        while (fileInput.eof() != true) {
            for (int i = 0; i < 14; i++){
                std::getline(fileInput, line);
                if (i > 0){
                    frame += "\n";
                    frame += line;
                }
                else{
                    try{
                        frameCount = std::stoi(line);
                    }
                    catch (std::exception e){
                        std::cout << "Read to end of file"  <<std::endl;
                    }
                }
            }
            for (int i = 0; i < frameCount; i++){
                mFilm.push_back(frame);
            }
            frame.clear();
        }
    }
//        std::cout << "Loaded frames:" << std::endl;
//        for (const std::string& frame : mFilm) {
//            std::cout<< "nexst frame" << std::endl;
//            std::cout << frame << std::endl;
//        }
    
}
