#ifndef NOTE_H
#define NOTE_H

class Note
{
public:
    Note();

private:
    int start, duration;
    bool triggered;
    int key;
};

#endif // NOTE_H
