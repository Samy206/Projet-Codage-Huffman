cmake_minimum_required(VERSION 2.8.11)

project(Partie3Cryptage)

find_package(Qt5 5.0.1 REQUIRED COMPONENTS
    Core Gui Widgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
    Headers/Partie2/Sommet.h 
    Headers/Partie2/ArbreB.h 
    Headers/Partie2/Lecteur.h 
    Headers/Partie2/Cryptage.h 
    Headers/Partie2/Decryptage.h 
    Headers/GUI/DessineArbre.h 
    Headers/GUI/MainWindow.h 
    Headers/GUI/GetUserText.h 
    Headers/GUI/DisplayResults.h 
    Headers/GUI/Context.h 

    Sources/Partie2/Sommet.cc 
    Sources/Partie2/ArbreB.cc 
    Sources/Partie2/Lecteur.cc 
    Sources/Partie2/Cryptage.cc 
    Sources/Partie2/Decryptage.cc 
    Sources/GUI/DessineArbre.cc 
    Sources/GUI/MainWindow.cc 
    Sources/GUI/GetUserText.cc 
    Sources/GUI/Context.cc 
    Sources/GUI/graphicMain.cc

    ../qdarkstyle/style.qrc
)

target_link_libraries(${PROJECT_NAME}

    Qt5::Core Qt5::Gui Qt5::Widgets

)
