/***************************************************************************************
Header file : ResultsList.hpp
Description : Declaration of classes PL_Node,PostingList which are used to
              represent results list which contains all the results of a join query.
****************************************************************************************/
#ifndef RES_LIST_H
#define RES_LIST_H

// #define BUCKET_SIZE 1024*1024
#define BUCKET_SIZE 10*10
#define RESULT_SIZE_VAL1 15
#define RESULT_SIZE_VAL2 7

#include <stdint.h>
#include <cstring>
#include <cstdlib>
#include <iostream>

struct Result{
    int32_t* value1; /* To be changed */
    int32_t* value2; /* To be changed */
};

class BucketNode{

private:
        BucketNode *next;
        int offset; /* Current offset from the beggining of the current bucket */
public:
        int32_t* my_results; /* This field is public so as we can use it from ResultsList class */
        BucketNode();
        ~BucketNode();
        BucketNode* GetNext();
        void SetNext(BucketNode* my_next);
        int GetOffset();
        void SetOffset( int new_offset );
};

class ResultsList{

private:
        BucketNode *first;
        BucketNode *last;
        int num_of_buckets;
        int num_of_results;
public:
        ResultsList();
        ~ResultsList();
        void Insert( Result& result_to_insert );
        int GetBucketsNum();
        int GetResultsNum();
        bool IsEmpty();
        void PrintResults();
        BucketNode* GetFirst();
};

#endif /* RES_LIST_H */
