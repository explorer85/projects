#ifndef ABSTRACTALGOCREATOR_H
#define ABSTRACTALGOCREATOR_H

class AbstractAlgo;
class QString;

class AbstractAlgoCreator {
public:
    virtual AbstractAlgo* create() = 0;
    virtual QString getType() const = 0;
    virtual ~AbstractAlgoCreator() {}
};

#endif // ABSTRACTALGOCREATOR_H
