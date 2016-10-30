#ifndef TIMSORT_PARAMETERS_H
#define TIMSORT_PARAMETERS_H

enum EWhatMerge {
    WM_NoMerge, WM_MergeXY, WM_MergeYZ
};

class IParameters {
public:
    virtual unsigned minRun(unsigned n) const = 0;
    virtual bool needMerge(unsigned lenX, unsigned lenY) const = 0;
    virtual EWhatMerge whatMerge(unsigned lenX, unsigned lenY, unsigned lenZ) const = 0;
    virtual unsigned getGallop() const = 0;
    virtual ~IParameters() {};
};

class DefaultParameters: public IParameters {
    virtual unsigned minRun(unsigned n) const {
        int r = 0;
        while (n >= 64) {
            r |= n & 1;
            n >>= 1;
        }
        return r + n;
    }

    virtual bool needMerge(unsigned lenX, unsigned lenY) const {
        return lenX <= lenY;
    }

    virtual EWhatMerge whatMerge(unsigned lenX, unsigned lenY, unsigned lenZ) const {
        if (lenZ >= lenY || lenY + lenZ >= lenX)
            return WM_MergeYZ;
        return WM_NoMerge;
    }

    virtual unsigned getGallop() const {
        return 7;
    }
};

#endif //TIMSORT_PARAMETERS_H
