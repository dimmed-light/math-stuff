// depends on PixelGameEngine so have a look at the dependencies in the 
// project's GitHub page
// flags: -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20
#define OLC_PGE_APPLICATION
#include "../lib/olcPixelGameEngine.h"

#include "../lib/math_stuff.h"
#include <list>
#include <vector>
#include <functional>
#include <cstdint>

class UlamSpiral : public olc::PixelGameEngine {
public:
    UlamSpiral() {
        sAppName = "Ulam spiral";
    }

    enum class Direction {
        up,
        down,
        left,
        right
    };

    using Location = olc::vi2d;
    using Point = std::pair<unsigned int, Location>;

    // takes the old direction and returns the new direction and a function that 
    // makes a step towards that direction
    // ex. if the current direction is down then it returns the new direction
    // function that moves us to the right
    static std::pair<Direction, std::function<Location(Location, uint8_t)>> 
    getNewDirectionFunction(Direction currentDirection) {
        switch(currentDirection) {
            case Direction::down:
                // new direction is right
                return {
                    Direction::right, 
                    [] (Location previousLocation, uint8_t step) -> Location {
                        return { 
                            previousLocation.x + step, 
                            previousLocation.y 
                        };
                    } 
                };
            case Direction::right:
                // new direction is up
                return { 
                    Direction::up,
                    [] (Location previousLocation, uint8_t step) -> Location {
                        return { 
                            previousLocation.x, 
                            previousLocation.y - step 
                        };
                    }
                };
            case Direction::up:
                // new direction is left
                return {
                    Direction::left,
                    [] (Location previousLocation, uint8_t step) -> Location {
                        return { 
                            previousLocation.x - step, 
                            previousLocation.y 
                        };
                    }
                };
            case Direction::left:
                // new direction is down
                return {
                    Direction::down,
                    [] (Location previousLocation, uint8_t step) -> Location {
                        return { 
                            previousLocation.x, 
                            previousLocation.y + step 
                        };
                    }
                };
            default:
                break;
        }
        return {
            currentDirection,
            [] (Location previousLocation, uint8_t step) {
                return previousLocation;
            }
        };
    }

    // This function makes a "row" of Locations in the spiral
    // A row is a set of Locations that are next to each other and in the same 
    // direction 
    static std::pair<Direction, std::vector<Location>> 
    makeLocations(
        Direction currentDirection, 
        Location previousLocation,
        unsigned int pointsInCurrentDirection,
        uint8_t step
    ) {
        auto [
            newDirection, 
            newDirectionFunction
        ] = getNewDirectionFunction(currentDirection);
        std::vector<Location> locations;
        for (unsigned int i = 0; i < pointsInCurrentDirection; i++) {
            Location newLocation = newDirectionFunction(previousLocation, step);
            locations.push_back(std::move(newLocation));
            previousLocation = newLocation;
        }
        return { newDirection, locations };
    }

    static std::vector<Point> makeSpiral(
        unsigned int l, 
        Location startingLocation
    ) {
        std::vector<Point> points;
        unsigned int n = 1;
        points.push_back({ n, startingLocation });

        // this is the distance between points
        const uint8_t step = 1;

        // so that we start from right (see getNewDirectionFunction)
        Direction currentDirection = Direction::down;
        
        Location currentLocation = startingLocation;

        unsigned int pointsInCurrentDirection = 1;
        // counter to make pointsInCurrentDirection increment for every second 
        // row of locations
        unsigned int c = 0;

        while (n < l) {
            std::vector<Location> newLocations;
            std::tie(
                currentDirection, 
                newLocations
            ) = makeLocations(
                currentDirection, 
                currentLocation, 
                pointsInCurrentDirection,
                step
            );
            for (auto& location : newLocations) {
                points.push_back({ ++n,  location});
            }
            
            // make pointsInCurrentDirection increment for every second row
            if (c == 1) {
                c = 0;
                pointsInCurrentDirection++;
            } else {
                c++;
            }

            // the second item is location (aka olc::vi2d)
            currentLocation = points.back().second;
        }

        return points;
    }

    bool OnUserCreate() override {
        const unsigned int numberOfPoints = 100000;

        std::vector<Point> initialSpiral = makeSpiral(
            numberOfPoints, 
            { ScreenWidth() / 2, ScreenHeight() / 2 }
        );
        
        std::list<unsigned int> primes = mst::sieve_of_eratosthenes(
            mst::count_primes(1, numberOfPoints)
        );
        auto primeIterator = primes.begin();

        for (auto& point : initialSpiral) {
            auto& [ n, loc ] = point;
            if (n == *primeIterator) {
                ulamSpiralLocations.push_back(std::move(loc));
                primeIterator++;
            }
        }
        
        return true;
    }

    bool OnUserUpdate(float elapsedTime) override {
        for (auto& location : ulamSpiralLocations) {
		    Draw(location.x, location.y, olc::WHITE);	
        }
		return true;
    }
private:
    std::vector<Location> ulamSpiralLocations;
};

int main() {
    UlamSpiral application;
    if (application.Construct(100, 100, 4, 4)) {
        application.Start();
    }
    return 0;
}
