#include <iostream>
#include <vector>
/*
#include "quick_sort.h"
#include <chrono>
*/
#include "dual_sort.h"
#include <random>
#include "n_dim_sort.h"
#include "woodpecker.hpp"

TEST("Rendezes") {
    {
        // Ures vektor
        std::vector<int> test_array{};
        dual_sort(test_array, 0);
        CHECK_EQ(true, is_sorted(test_array.begin(), test_array.end()));
    }

    {
        // Egy elem
        std::vector<int> test_array{1};
        dual_sort(test_array, 1);
        CHECK_EQ(true, is_sorted(test_array.begin(), test_array.end()));
    }

    {
        // Ket elem, rendezett
        std::vector<int> test_array{1, 4};
        dual_sort(test_array, 2);
        CHECK_EQ(true, is_sorted(test_array.begin(), test_array.end()));
    }

    {
        // Ket elem, rendezetlen
        std::vector<int> test_array{5, 2};
        dual_sort(test_array, 2);
        CHECK_EQ(true, is_sorted(test_array.begin(), test_array.end()));
    }

    {
        // Keves elem
        std::vector<int> test_array{1, 3, 4, 2, 0, -1};
        dual_sort(test_array, 6);
        CHECK_EQ(true, is_sorted(test_array.begin(), test_array.end()));
    }

    {
        // 3 elem, nem kell felosztani
        std::vector<int> test_array{2, 1, 3};
        dual_sort(test_array, 3);
        CHECK_EQ(true, is_sorted(test_array.begin(), test_array.end()));
    }

    {
        // 3 elem, fel kell osztani
        std::vector<int> test_array{2, 3, 1};
        dual_sort(test_array, 3);
        CHECK_EQ(true, is_sorted(test_array.begin(), test_array.end()));
    }

    constexpr unsigned N = 99;
    constexpr unsigned num = 30;
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, N);
    std::vector<int> test_array(num);
    for (int i = 0; i < 10; ++i) {
        for (unsigned j = 0; j < num; ++j) {
            test_array[j] = dist(gen);
        }
    }
    dual_sort(test_array,test_array.size());
    CHECK_EQ(true, is_sorted(test_array.begin(), test_array.end()));
}

TEST("2D rendezes") {
    constexpr unsigned N = 99;
    constexpr unsigned num = 30;
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, N);
    std::vector<int> test_array(num);
    for (int i = 0; i < 10; ++i) {
        for (unsigned j = 0; j < num; ++j) {
            test_array[j] = dist(gen);
        }
    }
    std::vector<std::vector<int>> result = sort_2D(test_array);
    CHECK_EQ(true, result[0][0] <= result [1][0]);
    CHECK_EQ(true, result[0][0] <= result [2][3]);
    CHECK_EQ(true, result[5][0] <= result [3][4]);
    CHECK_EQ(true, result[3][4] <= result [0][5]);
    CHECK_EQ(true, result[3][3] <= result [3][4]);
}

TEST("3D rendezes") {
    constexpr unsigned N = 99;
    constexpr unsigned num = 30;
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, N);
    std::vector<int> test_array(num);
    for (int i = 0; i < 10; ++i) {
        for (unsigned j = 0; j < num; ++j) {
            test_array[j] = dist(gen);
        }
    }
    std::vector<std::vector<std::vector<int>>> result = sort_3D(test_array);
    CHECK_EQ(true, result[0][0][0] <= result [1][0][0]);
    CHECK_EQ(true, result[1][1][0] <= result [1][0][1]);
    CHECK_EQ(true, result[1][1][0] <= result [0][1][1]);
    CHECK_EQ(true, result[1][1][0] <= result [1][1][1]);
    CHECK_EQ(true, result[2][1][0] <= result [1][1][2]);
}

/// Erdekes resz (opcionalis), probald ki, ha kulon megirtad a quick_sort.h-t!
/*
using real_sec = std::chrono::duration<double, std::ratio<1>>;

TEST("Altalaban jobb mint a quicksort kis elemszam eseten") {
    constexpr unsigned N = 32;
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, N);
    std::vector<int> init(N);
    // total times in seconds
    double quicksort_total_time = 0.0, solution_total_time = 0.0;
    for (int i = 0; i < 1000; ++i) {
        for (unsigned j = 0; j < N; ++j) {
            init[j] = dist(gen);
        }
        std::vector<int> sortArray = init;
        TIMER(quicksort_short) {
            quick_sort(sortArray, 0, sortArray.size() - 1);
        }
        quicksort_total_time += std::chrono::duration_cast<real_sec>(quicksort_short).count();
        sortArray = init;
        TIMER(solution_short) {
            dual_sort(sortArray, sortArray.size());
        }
        solution_total_time += std::chrono::duration_cast<real_sec>(solution_short).count();
    }
    std::cout << "quick_sort: " << quicksort_total_time << "s\n";
    std::cout << "dual_sort: " << solution_total_time << "s\n";
    CHECK_EQ(true, quicksort_total_time > solution_total_time);
}

TEST("Altalaban jobb, mint a quicksort tobb elem eseten") {
    constexpr unsigned N = 1000;
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, N);
    std::vector<int> init(N);
    // total times in seconds
    double quicksort_total_time = 0.0, solution_total_time = 0.0;
    for (int i = 0; i < 100; ++i) {
        for (unsigned j = 0; j < N; ++j) {
            init[j] = dist(gen);
        }
        std::vector<int> sortArray = init;
        TIMER(quicksort_medium) {
            quick_sort(sortArray, 0, sortArray.size() - 1);
        }
        quicksort_total_time +=
                std::chrono::duration_cast<real_sec>(quicksort_medium).count();
        sortArray = init;
        TIMER(solution_medium) {
            dual_sort(sortArray, sortArray.size());
        }
        solution_total_time += std::chrono::duration_cast<real_sec>(solution_medium).count();
    }
    std::cout << "quick_sort: " << quicksort_total_time << "s\n";
    std::cout << "dual_sort: " << solution_total_time << "s\n";
    CHECK_EQ(true, quicksort_total_time > solution_total_time);
}

TEST("Legrosszabb eset") {
    constexpr unsigned N = 1 << 13;
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, N);
    std::vector<int> init(N);
    for (unsigned j = 0; j < N; ++j) {
        init[j] = j;
    }
    // total times in seconds
    double quicksort_total_time = 0.0, solution_total_time = 0.0;
    for (int i = 0; i < 5; ++i) {
        std::vector<int> sortArray = init;
        TIMER(quicksort_short) {
            quick_sort(sortArray, 0,
                      sortArray.size() - 1); // Ehhez a teszthez a quicksortban mindig
            // az elso elem legyen a pivot.
        }
        quicksort_total_time += std::chrono::duration_cast<real_sec>(quicksort_short).count();
        sortArray = init;
        TIMER(solution_short) {
            dual_sort(sortArray, sortArray.size());
        }
        solution_total_time += std::chrono::duration_cast<real_sec>(solution_short).count();
    }
    std::cout << "quick_sort: " << quicksort_total_time << "s\n";
    std::cout << "dual_sort: " << solution_total_time << "s\n";
    CHECK_EQ(true, quicksort_total_time > solution_total_time);
}
*/


WOODPECKER_MAIN()
