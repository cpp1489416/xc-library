#ifndef DFSMAZE_H
#define DFSMAZE_H


namespace Xc
{
    class DFSMaze
    {
    public:
        struct Location
        {
        public:
            Location(int row, int column) :
                mRow(row), mColumn(column)
            {
            }

            int mRow;
            int mColumn;
        };

    public:
        DFSMaze(int width, int height);
        ~DFSMaze();
        void print();
        void solve();
        int width() const { return mWidth; }
        int height() const { return mHeight; }

    private:
        void init();
        void buildMap(int startRow, int startColumn);
        int getPossible(Location location);

        int mWidth;
        int mHeight;
        static const int MAXN = 100;
        char mMap[MAXN][MAXN];
        bool mVis[MAXN][MAXN];
        const char WALL = '@';
        const char ROAD = ' ';
        const char STEP = '.';
    };
}

#endif // DFSMAZE_H

