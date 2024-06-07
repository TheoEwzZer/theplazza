/*
** EPITECH PROJECT, 2024
** theplazza
** File description:
** Reception
*/

#include "Kitchen.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "SafeQueue.hpp"
#include "ScopedLock.hpp"
#include <list>
#include <memory>
#include <queue>
#include <string>

using std::string;
using std::ofstream;
using std::unique_ptr;
using std::mutex;
using std::list;
using std::pair;

namespace plazza {
    class Reception {
        public:
            Reception(
                const double multiplier, const long cooks, const long time)
                : mMultiplier(multiplier), mCooks(cooks), mTime(time) {}
            void startPlazza();
            void iterateKitchens(IPizza *pizza);
            void processOrder(const string &order);
            void addPizza(
                const PizzaType type, const PizzaSize size, const int quantity
            );
            PizzaSize getSize(const string &size) const;
            PizzaType getType(const string &type) const;

            unique_ptr<IPipe> createPipe(
                const string &pipeName, const bool isInPipe
            );
            pair<PipeIn *, PipeOut *> createKitchen();
        private:
            double mMultiplier = 0.0;
            long mCooks = 0;
            long mTime = 0;
            SafeQueue<unique_ptr<IPizza>> mPizzas;
            list<pair<PipeIn *, PipeOut *>> mKitchens;
            Mutex mMutex;
            int mKitchenNumber = 0;
            unique_ptr<Logger> mLogger = make_unique<Logger>();
    };
}
