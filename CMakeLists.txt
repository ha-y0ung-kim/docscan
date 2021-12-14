cmake_minimum_required(VERSION 2.8)
project( main )
set("OpenCV_DIR" "ocv-build")
set("Leptonica_DIR" "leptonica_build")
set("Tesseract_DIR" "tesseract_build")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
# add_executable( main main.cpp )
# target_link_libraries( main ${OpenCV_LIBS} )
# add_executable( docscan docscan.cpp )
# target_link_libraries( docscan ${OpenCV_LIBS} )
# add_executable( f f.cpp )
# target_link_libraries( f ${OpenCV_LIBS} )
# add_executable( findedge findedge.cpp )
# target_link_libraries( findedge ${OpenCV_LIBS} )


# add_executable( imagesizetranform imagesizetranform.cpp )
# target_link_libraries( imagesizetranform ${OpenCV_LIBS} )


find_package( Leptonica REQUIRED ) 
include_directories(${Leptonica_INCLUDE_DIRS})


find_package( Tesseract REQUIRED ) 
include_directories(${Tesseract_INCLUDE_DIRS})

add_executable( ocrtry ocrtry.cpp )
target_link_libraries( ocrtry ${OpenCV_LIBS} ${TESSERACT_LIBRARIES} ${LEPTONICA_LIBRARIES})
target_link_libraries( ocrtry -llept -ltesseract)

# cmake_minimum_required(VERSION 2.8)
# project( DisplayImage )
# find_package( OpenCV REQUIRED )
# include_directories( ${OpenCV_INCLUDE_DIRS} )
# add_executable( DisplayImage DisplayImage.cpp )
# target_link_libraries(DisplayImage ${OpenCV_LIBS})
 # must add this line to link Tesseract and leptonica libs
