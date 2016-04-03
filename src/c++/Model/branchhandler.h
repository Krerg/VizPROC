#ifndef BRANCHHANDLER_H
#define BRANCHHANDLER_H

#include <QObject>
#include "src/c++/Model/branch.h"

class BranchHandler : public QObject
{
    Q_OBJECT
public:
    explicit BranchHandler(QObject *parent = 0);

    static Branch *unionBranch(Branch* branch1, Branch* branch2);

signals:

public slots:

};

#endif // BRANCHHANDLER_H
