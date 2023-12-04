#include "TerrainMap.h"
#include "Path.h"
#include "Letadlo.h"
#include "Lod.h"

#include <vector>
#include <iostream>
#include <string>


// Include files of your path classes will need to be added here

//Point read_coordinates(int argc, char* argv[], int i_option) {
//    Point p;
//
//    if (argc > i_option + 1) { p.x = std::atoi(argv[i_option]); p.y = std::atoi(argv[i_option + 1]); }
//    else throw std::runtime_error("Coordinates incorrectly specified!");
//
//    return p;
//}

int main(int argc, char* argv[]) {
    const int nx = 256;
    const int ny = 256;

    cout << "444444444444" << endl;


    std::string terrain_filename;

    // Load the terrain map

    if (argc > 1) { terrain_filename = argv[1]; }
    else { std::cout << "No terrain file specified!" << std::endl; }
    terrain_filename = "terrain.dat";

    TerrainMap m(nx, ny, terrain_filename);

    // Load the coordinates of the start and end points

    Point start(198, 205);// = read_coordinates(argc, argv, 2);
    Point finish(78, 17);// = read_coordinates(argc, argv, 4);

    std::cout << "Start coordinates: [" << start.x << ", " << start.y << "]" << std::endl;

    std::vector<Path*> paths = {
    //    new Lod(m,"Lod",start,finish),
        new Letadlo(m,"Letadlo",start,finish),
    //    new Silnice(m,"Silnice",start,finish),
    //    new Siljekt(m,"Siljekt",start,finish),
    //    new Vlak(m,"Vlak",start,finish)*/
    //    // Here add the list of dynamically created classes with path finding algorithms
    };

    //double L = letadlo(m, "Letadlo", start, finish);

    for (auto& p : paths) {
        std::cout << "Path search: " << p->getName() << std::endl;
        std::cout << "=============" << std::endl;
        p->find();
        p->printStats();
        std::cout << "=============" << std::endl;
        p->saveToFile();
        delete p;
    }
    

    return 0;
}