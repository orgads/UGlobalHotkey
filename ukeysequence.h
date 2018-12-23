#pragma once

#include <QObject>
#include <QLoggingCategory>
#include <QString>
#include <QVector>
#include <QStringList>
#include <QKeyEvent>

#include "uglobal.h"

Q_DECLARE_LOGGING_CATEGORY(ughDebug)

class UGLOBALHOTKEY_EXPORT UKeySequence : public QObject
{
    Q_OBJECT

public:
    explicit UKeySequence(QObject *parent = nullptr);
    explicit UKeySequence(const QString &str, QObject *parent = nullptr);

    void fromString(const QString &str);
    QString toString();
    void addKey(Qt::Key key);
    void addKey(const QString &key);
    void addModifiers(Qt::KeyboardModifiers mod);
    void addKey(const QKeyEvent *event);

    inline int size() const
    {
        return mKeys.size();
    }
    inline Qt::Key operator [](int n) const
    {
        if (n > mKeys.size()) {
            return Qt::Key_unknown;
        }

        return mKeys[n];
    }

    QVector<Qt::Key> getSimpleKeys() const;
    QVector<Qt::Key> getModifiers() const;

private:
    QVector<Qt::Key> mKeys;

    inline static bool isModifier(Qt::Key key)
    {
        return (key == Qt::Key_Shift ||
                key == Qt::Key_Control ||
                key == Qt::Key_Alt ||
                key == Qt::Key_Meta);
    }

    inline static QString keyToStr(int key)
    {
        if (key == Qt::Key_Shift) {
            return "Shift";
        }
        if (key == Qt::Key_Control) {
            return "Ctrl";
        }
        if (key == Qt::Key_Alt) {
            return "Alt";
        }
        if (key == Qt::Key_Meta) {
            return "Meta";
        }

        QKeySequence seq(key);
        return seq.toString();
    }

};
