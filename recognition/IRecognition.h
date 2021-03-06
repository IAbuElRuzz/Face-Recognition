/*
 * File:   IRecognition.h
 * Author: Octavian Sima 
 *
 * Declares recognition interface using CppInterfaces.h
 * These methods are called by network module 
 */


#ifndef _IRECOGNITION_H
#define	_IRECOGNITION_H

#include "CppInterfaces.h"

using namespace std;

/*
 * Structure that keeps recognition result
 */
struct RecognitionResult {
    vector<int> personIDArr;    //vector of best recognized personIDs;
                                //if personID = 0 -> face was not recognized
    vector<float> confidenceArr;//vector of best recognition confidences
};


DeclareInterface(IRecognition)

    /* Sets recognition type and parameters
     * recognitionThreshold - the minimum accepted percent for a person
     *          to be considered recognized
     * distanceType - type of distance used in closest face computation
     *     values: EUCLIDIAN_DISTANCE
     *             MAHALANOBIS_DISTANCE (provides better results)
     * faceImageExtension - image file type (pgm, jpg, etc.)
     * defaultTrainingDataFile - default xml file with training data
     */
    virtual int initialize(float recognitionThreshold, int distanceType,
            char* faceImageExtension, char* defaultTrainingDataFile) = 0;

    /*
     * Performs training phase - learn faces
     * trainingSetSourceType - training face images source type
     *    values: FILE_SRC  - face images from a file
     *                      - each line contains: subjectID faceImage_Path
     *            DATABASE_SRC - all faces from a given database
     * pathToTrainingSet - path to File or to Database
     * saveEigenFaces - if true, save eigenfaces and average image to out files
     */
    virtual int train(int trainingSetSourceType, char* pathToTrainingSet,
            bool saveEigenFaces)  = 0;

    /*
     * Saves data from trainng phase into a given xml file
     * if fileName = NULL -> defaultTrainingDataFile is used
     */
    virtual int saveTrainingData(char* fileName) = 0;

    /*
     * Loads training data from a given xml file
     * if fileName = NULL -> defaultTrainingDataFile is used
     */
    virtual int loadTrainingData(char* fileName) = 0;

    /*
     * Returns a vector of structs with recognized person IDs and
     * recognition confidence for the given faces
     *  faces - vector of faces to recognize
     *  resultsNo - number of best results for each face
     *            - if best result for a face is under recognitionThreshold,
     *              resultsNo will be 1 and personID will be 0
     * Obs: face images must have the same dimension with database images
     */
    virtual vector<RecognitionResult> recognizeFaces(vector<IplImage*> faces,
            int resultsNo) = 0;

    /*
     * Function used for testing recognition performance
     *  facesFilePath - path to file that contains on each line info like:
     *      faceImagePath  personRealID
     * Recognition results for each face from file will be shown at system out
     * Obs1: testing face images must have the same dimension with database images
     * Obs2: you should first call train() or loadTrainingData() functions before
     * calling this
     */
    virtual void testRecognitionPerformance(char* facesFilePath) = 0;
   
    
EndInterface


#endif	/* _IRECOGNITION_H */

