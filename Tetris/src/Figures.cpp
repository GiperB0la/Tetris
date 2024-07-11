#include "../include/Figures.h"

void Figures::DoFugureO() {
    std::vector<std::vector<std::string>> figure;
    figure.push_back({
        "######",
        "######",
        "######",
        "######"
        });
    figure.push_back({
        "######",
        "######",
        "######",
        "######"
        });
    figures.push_back(figure);
}

void Figures::DoFugureI() {
    std::vector<std::vector<std::string>> figure;
    figure.push_back({
        "###",
        "###",
        "###",
        "###",
        "###",
        "###"
        });
    figure.push_back({
        "############",
        "############"
        });
    figures.push_back(figure);
}

void Figures::DoFugureS() {
    std::vector<std::vector<std::string>> figure;
    figure.push_back({
        "   ######",
        "   ######",
        "######   ",
        "######   "
        });
    figure.push_back({
        "###   ",
        "###   ",
        "######",
        "######",
        "   ###",
        "   ###"
        });
    figures.push_back(figure);
}

void Figures::DoFugureZ() {
    std::vector<std::vector<std::string>> figure;
    figure.push_back({
        "######   ",
        "######   ",
        "   ######",
        "   ######"
        });
    figure.push_back({
        "   ###",
        "   ###",
        "######",
        "######",
        "###   ",
        "###   "
        });
    figures.push_back(figure);
}

void Figures::DoFugureL() {
    std::vector<std::vector<std::string>> figure;
    figure.push_back({
        "###",
        "###",
        "###",
        "###",
        "######",
        "######"
        });
    figure.push_back({
        "      ###",
        "      ###",
        "#########",
        "#########"
        });
    figures.push_back(figure);
}

void Figures::DoFugureJ() {
    std::vector<std::vector<std::string>> figure;
    figure.push_back({
        "   ###",
        "   ###",
        "   ###",
        "   ###",
        "######",
        "######"
        });
    figure.push_back({
        "###      ",
        "###      ",
        "#########",
        "#########"
        });
    figures.push_back(figure);
}

void Figures::DoFugureT() {
    std::vector<std::vector<std::string>> figure;
    figure.push_back({
        "#########",
        "#########",
        "   ###   ",
        "   ###   "
        });
    figure.push_back({
        "   ###   ",
        "   ###   ",
        "#########",
        "#########"
        });
    figures.push_back(figure);
}