//
// Created by morak on 2021. 11. 18..
//

#ifndef SOLUTION_N_DIM_SORT_H
#define SOLUTION_N_DIM_SORT_H

#include <iostream>
#include <vector>
#include "dual_sort.h"
#include <cmath>

/**
 * 2D-be rendezi a megadott vektort
 *
 * @param v rendezendo vektor
 * @return rendezett 2D matrix
 */

struct squarematrix{
    int x;
    int y;
    int value;
    int tavolsagnegyzet;
    squarematrix(int x,int y,int tavolsagnegyzet): x(x),y(y),tavolsagnegyzet(tavolsagnegyzet){
        value = 0;
    };
};

std::vector<std::vector<squarematrix>> matrixfeltolt(std::vector<std::vector<squarematrix>> vec, int size){
    std::vector<squarematrix> elsosor;
    for (int i = 0; i < size; i++){
        vec.push_back(elsosor);
        for (int j = 0; j < size; j++){
                vec[i].push_back(squarematrix(i,j,i*i+j*j)); //ez nem tömb akkor hozzá kell adni az elemeket mert eredetileg 0-0 a méret
            }
    }
    return vec;
}

std::vector<squarematrix> matrixegysorban(std::vector<std::vector<squarematrix>> vec,std::vector<squarematrix> vect, int size){
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                vect.push_back(vec[i][j]);
            }
        }
    return vect;
}


void dualmin_sort(std::vector<squarematrix> &vec){//minkiválasztásos rendezés
    int min;
    for(int i = 1;i < vec.size()-1;i++) {
        min = i;
        for (int j = i + 1; j < vec.size(); j++) {
            if (vec[min].tavolsagnegyzet > vec[j].tavolsagnegyzet) {
                min = j;
            }
        }
        squarematrix seged = vec[i];
        vec[i] = vec[min];
        vec[min] = seged;
    }
    for(int i = 0;i < vec.size()-2;i++) {
        for (int j = i + 1;j < vec.size()-1;j++) {
                if (vec[i].tavolsagnegyzet == vec[j].tavolsagnegyzet) {
                    if (vec[i].x < vec[j].x) {
                        squarematrix seged = vec[i];
                        vec[i] = vec[j];
                        vec[j] = seged;
                    }
                }
        }
    }
}

void matrixsort(std::vector<int> vec,std::vector <std::vector<squarematrix>> &vect,std::vector<squarematrix> &vec1d){
    for (int i = 0; i < vec.size(); i++) {//sima elemeket a mátrix 1d-nek átadjuk
        vec1d[i].value = vec[i];
    }
    for (int k = 0; k < vec1d.size(); k++) {
                vect[vec1d[k].x][vec1d[k].y].value = vec1d[k].value;
    }
}




std::vector<std::vector<int>> sort_2D(std::vector<int> v) {
    std::vector <std::vector<squarematrix>> vec;
    int size = sqrt(v.size())+1;
    std::vector<squarematrix> vect;
    dual_sort(v,v.size());
    vec = matrixfeltolt(vec,size);
    vect = matrixegysorban(vec,vect,size);
    dualmin_sort(vect);
    matrixsort(v,vec,vect);

    std::vector <std::vector<int>> vecmatrix;
    for (int i = 0; i < size; i++) {
        std::vector<int> ures;
        vecmatrix.push_back(ures);
        for (int j = 0; j < size; j++) {
            vecmatrix[i].push_back(vec[i][j].value);
        }
    }
    return vecmatrix;
}

/**
 * 3D-be rendezi a megadott vektort
 *
 * @param v rendezendo vektor
 * @return rendezett 3D matrix
 */

struct squarematrix2{
    int x;
    int y;
    int z;
    int value;
    int tavolsagnegyzet;
    squarematrix2(int x,int y,int z,int tavolsagnegyzet): x(x),y(y),z(z),tavolsagnegyzet(tavolsagnegyzet) {
        value = 0;
    };
};



std::vector<std::vector<std::vector<squarematrix2>>> matrixfeltolt2(std::vector<std::vector<std::vector<squarematrix2>>> vec, int size){
    std::vector<squarematrix2> elsosor;
    std::vector<std::vector<squarematrix2>> masodiksor;
    masodiksor.push_back(elsosor);
    for (int i = 0; i < size; i++){
        vec.push_back(masodiksor);
        for (int j = 0; j < size; j++) {
            vec[i].push_back(elsosor);
            for(int k = 0;k < size;k++) {
                vec[i][j].push_back(squarematrix2(i, j, k, i * i + j * j + k * k)); //ez nem tömb akkor hozzá kell adni az elemeket mert eredetileg 0-0 a méret
            }
        }
    }
    return vec;
}

std::vector<squarematrix2> matrixegysorban2(std::vector<std::vector<std::vector<squarematrix2>>> vec,std::vector<squarematrix2> vect, int size){
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for(int k = 0;k < size;k++)
                vect.push_back(vec[i][j][k]);
            }
        }
    return vect;
}

void dualmin_sort2(std::vector<squarematrix2> &vec) {//minkiválasztásos rendezés
    int min;
    for(int i = 1;i < vec.size()-1;i++) {
        min = i;
        for (int j = i + 1; j < vec.size(); j++) {
            if (vec[min].tavolsagnegyzet > vec[j].tavolsagnegyzet) {
                min = j;
            }
        }
        squarematrix2 seged = vec[i];
        vec[i] = vec[min];
        vec[min] = seged;
    }

    for (int i = 0;i < vec.size() - 2; i++) {
        for (int j = i + 1; j < vec.size()-1; j++) {
            for (int k = i+2;k < vec.size(); k++) {
                if (vec[i].tavolsagnegyzet == vec[j].tavolsagnegyzet) {
                    if (vec[i].x < vec[j].x) {
                        squarematrix2 seged = vec[i];
                        vec[i] = vec[j];
                        vec[j] = seged;
                    }else if (vec[i].y < vec[j].y && vec[i].x == vec[j].x){
                        squarematrix2 seged = vec[i];
                        vec[i] = vec[j];
                        vec[j] = seged;
                    }
                }
                if(vec[i].tavolsagnegyzet == vec[j].tavolsagnegyzet == vec[k].tavolsagnegyzet){
                    if(vec[i].x < vec[j].x){
                        if(vec[i].x > vec[k].x){
                            squarematrix2 seged = vec[i];
                            vec[i] = vec[k];
                            vec[k] = seged;
                        }else if(vec[i].x == vec[k].x){
                            if(vec[i].y < vec[k].y){
                                squarematrix2 seged = vec[i];
                                vec[i] = vec[k];
                                vec[k] = seged;
                            }
                        }
                    }else if(vec[i].x == vec[j].x){
                        if(vec[i].y < vec[j].y){
                            squarematrix2 seged = vec[i];
                            vec[i] = vec[j];
                            vec[j] = seged;
                        }
                    }
                }
            }
        }
    }
}

void matrixsort2(std::vector<int> vec,std::vector<std::vector <std::vector<squarematrix2>>> &vect,std::vector<squarematrix2> &vec1d){
    for (int i = 0; i < vec.size(); i++) {//sima elemeket a mátrix 1d-nek átadjuk
        vec1d[i].value = vec[i];
    }
    for (int k = 0; k < vec1d.size(); k++) {
        vect[vec1d[k].x][vec1d[k].y][vec1d[k].z].value = vec1d[k].value;
    }
}


std::vector<std::vector<std::vector<int>>> sort_3D(std::vector<int> v) {
    std::vector<std::vector <std::vector<squarematrix2>>> vec;
    int size = sqrt(v.size())+1;
    std::vector<squarematrix2> vect;
    dual_sort(v,v.size());
    vec = matrixfeltolt2(vec,size);
    vect = matrixegysorban2(vec,vect,size);
    dualmin_sort2(vect);
    matrixsort2(v,vec,vect);

    std::vector<std::vector<std::vector<int>>> vecmatrix;
    std::vector<int> ures;
    std::vector<std::vector<int>> ures2;
    for (int i = 0; i < size; i++) {
        vecmatrix.push_back(ures2);
        for (int j = 0; j < size; j++) {
            vecmatrix[i].push_back(ures);
            for(int k = 0;k < size;k++) {
                vecmatrix[i][j].push_back(vec[i][j][k].value);
            }
        }
    }
    return vecmatrix;

}

#endif //SOLUTION_N_DIM_SORT_H
