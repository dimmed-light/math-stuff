// depends on PixelGameEngine so have a look at the dependencies in the 
// project's GitHub page
// flags: -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20
#define OLC_PGE_APPLICATION
#include "../lib/olcPixelGameEngine.h"

#include <vector>
#include <cmath>
#include <functional>
#include <numbers>

class Circle : public olc::PixelGameEngine {
public:
    Circle() {
        sAppName = "Circle";
    }

    using Spiral = std::vector<olc::vd2d>;
    
    static unsigned int calculateSize(double start, double end, double step) {
        const double distance = std::abs(start - end);
        const double absStep = std::abs(step);
        double size = distance / absStep;
        if (size - (unsigned int) size != 0) {
            size++;
        }
        return (unsigned int) size;
    }

    static Spiral makeSpiral(
        olc::vi2d center, 
        double begin, 
        double end,
        double step,
        std::function<double(double)> equation
    ) {
        if (
            (step == 0) || (end < begin && step > 0) || 
            (end > begin && step < 0)
        ) {
            return {};
        }

        std::vector<double> angles(calculateSize(begin, end, step));
        auto it = angles.begin();
        for (double angle = begin; angle < end; angle += step) {
            *it++ = angle;
        }

        std::vector<olc::vd2d> locations;
        for (double angle : angles) {
            double radius = equation(angle);
            locations.push_back(
                { 
                    center.x + (radius * std::cos(angle)), 
                    center.y + (radius * std::sin(angle)) 
                }
            );
        }
        return locations;
    }

    bool OnUserCreate() override {
        olc::vi2d const center { ScreenWidth() / 2, ScreenHeight() / 2 };

        spirals = {
            // Circle
            makeSpiral(
                center, 0, 400, 1, 
                [] (double angle) -> double {
                    return 100;
                }
            ),
            // Golden spiral
            makeSpiral(
                { ScreenWidth() / 2, ScreenHeight() / 2 },
                0, 20, 0.001,
                [] (double angle) -> double {
                    return std::pow(
                        std::numbers::phi_v<double>, 
                        2 * angle / std::numbers::pi_v<double>
                    );
                }
            ),
            // Atomic spiral
            makeSpiral(
                { ScreenWidth() / 2, ScreenHeight() / 2 },
                0, 400, .1,
                [] (double angle) -> double {
                    return 100 * (angle / (angle - 100));
                }
            )
        };

        return true;
    }

    bool OnUserUpdate(float elapsedTime) override {

        for (auto const& point : spirals[2]) {
		    Draw(point.x, point.y, olc::WHITE);	
        }
        
        return true;
    }

private:
    std::array<Spiral, 3> spirals;
};

int main() {
    Circle application;
    if (application.Construct(1024, 1024, 4, 4)) {
        application.Start();
    }
    return 0;
}
