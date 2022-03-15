//
// Created by morak on 2021. 11. 17..
//

#ifndef SOLUTION_DUAL_SORT_H
#define SOLUTION_DUAL_SORT_H

#include <iostream>
#include <vector>
#include <cmath>

/**
 * dual_sort fv a  megadott tartomanyon talalhato elemeket
 * rendezi novekvo sorrendbe.
 *
 * @param data rendezendo vektor
 * @param N rendezendo vektor merete
 */

int szetvalogat(std::vector<int> &data,int bal,int jobb){
    int seged = data[bal];
    while(bal < jobb){
        while((bal < jobb) and (data[jobb] > seged)){
            jobb = jobb-1;
        }
        if(bal < jobb){
            data[bal] = data[jobb];
            bal = bal+1;
            while((bal < jobb) and (data[bal] <= seged)){
                bal = bal+1;
            }
            if(bal < jobb){
                data[jobb] = data[bal];
                jobb = jobb-1;
            }
        }
    }
    int idx = bal;
    data[idx] = seged;
    return idx;
}


void kupacol(std::vector<int> &data,int N,int k,int i){
    int max = -2000;
    int bal = 2*i;
    int jobb=2*i+1;
    if((bal <= k) and (data[bal] > data[i])){
        max = bal;
    }else{
        max = i;
    }
    if((jobb <= k) and (data[jobb] > data[max])){
        max = jobb;
    }
    if(max != i){
        int seged = data[i];
        data[i] = data[max];
        data[max] = seged;
        kupacol(data,N,k,max);
    }
};

void kupacotepit(std::vector<int> &data,int N){
    for(int i = N/2;i > 1;i--){
        kupacol(data,N,N,i);
    }
};

void kupacrendezes(std::vector<int> &data,int N){
    kupacotepit(data,N);
    for(int i = N;i > 2;i--){
        int seged = data[1];
        data[1] = data[i];
        data[i] = seged;
        kupacol(data,N,i-1,1);
    }
}

void gyorsrendezes(std::vector<int> &data,int bal,int jobb,int k) {
    k++;
    int max = 2*std::log2(data.size());
    if(k < max) {
        int idx = szetvalogat(data, bal, jobb);
        if (idx > bal + 1) {
            gyorsrendezes(data, bal, idx - 1,k);
        }
        if (idx < jobb - 1) {
            gyorsrendezes(data, idx + 1, jobb,k);
        }
    }else{
        kupacrendezes(data,data.size());
    }
}

void dual_sort(std::vector<int> &data, int N) {
    gyorsrendezes(data,0,N-1,0);
}



#endif //SOLUTION_DUAL_SORT_H
