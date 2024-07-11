#ifndef FIGURES_H
#define FIGURES_H

#include <vector>
#include <string>

class Figures {
public:
    static Figures& GetFigures() {
        static Figures ObjFigures;
        return ObjFigures;
    }

    Figures(const Figures&) = delete;
    Figures& operator=(const Figures&) = delete;

    std::vector<std::vector<std::vector<std::string>>> figures;

private:
    Figures() {
        DoFugureO();
        DoFugureI();
        DoFugureS();
        DoFugureZ();
        DoFugureL();
        DoFugureJ();
        DoFugureT();
    }

    void DoFugureO();
    void DoFugureI();
    void DoFugureS();
    void DoFugureZ();
    void DoFugureL();
    void DoFugureJ();
    void DoFugureT();
};

#endif