#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int x = 0, int y = 0)
        : x(x)
        , y(y)
    {}
    
    bool operator==(const Point& other) {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const Point& other) {
        return !(*this == other);
    }

    friend bool operator<(const Point& lhs, const Point& rhs) {
        return (lhs.x < rhs.x) ||
               (lhs.x == rhs.x && lhs.y < rhs.y);
    }
};

class PathFinder {
    vector<vector<int>> m_weights;
    vector<vector<int>> m_values;
    vector<vector<bool>> m_decided;
    set<Point> m_candidates;
    Point m_curr;
    int m_rowCount;
    int m_colCount;

    void m_updateWeight(int dx, int dy) {
        int x = m_curr.x + dx;
        int y = m_curr.y + dy;
        if (x >= 0 && x < m_rowCount && y >= 0 && y < m_colCount && !m_decided[x][y]) {
            int weight = m_values[m_curr.x][m_curr.y] + m_weights[x][y];
            if (m_values[x][y] < 0 || m_values[x][y] > weight) {
                m_values[x][y] = weight;
            }
            m_candidates.insert(Point(x,y));
        }
    }

public:
    PathFinder(int row_count, int col_count)
        : m_weights(row_count, vector<int>(col_count, 0))
        , m_values(row_count, vector<int>(col_count, -1))
        , m_decided(row_count, vector<bool>(col_count, false))
        , m_candidates()
        , m_curr()
        , m_rowCount(row_count)
        , m_colCount(col_count)
    {}

    void feed(int data) {
        m_weights[m_curr.x][m_curr.y] = data;
        if (++m_curr.y == m_colCount) {
            m_curr.y = 0;
            m_curr.x ++;
        }
    }
    
    int findShortestPath(Point start, Point end) {
        for (int i = 0; i < m_rowCount; i++) {
            fill(m_values[i].begin(), m_values[i].end(), -1);
            fill(m_decided[i].begin(), m_decided[i].end(), false);
        }
        m_candidates.clear();
        m_curr = start;

        m_values[start.x][start.y] = m_weights[start.x][start.y];
        while (m_curr != end) {
            m_decided[m_curr.x][m_curr.y] = true;

            // Update values
            m_updateWeight(0, -1);
            m_updateWeight(0,  1);
            m_updateWeight(-1, 0);
            m_updateWeight( 1, 0);

            // pick-up the next node
            int min_value = m_values[m_curr.x][m_curr.y] + 3001;
            auto p_node = m_candidates.end();
            for (auto itor = m_candidates.begin(); itor != m_candidates.end(); ++itor) {
                if (m_values[itor->x][itor->y] < min_value) {
                    p_node = itor;
                    min_value = m_values[itor->x][itor->y];
                }
            }

            if (p_node == m_candidates.end()) {
                break;
            }

            m_curr = *p_node;
            m_candidates.erase(p_node);
        }

        return m_values[end.x][end.y];
    }
};

int main(void) {
    int row_count, col_count;
    cin >> row_count >> col_count;
    PathFinder pathFinder(row_count, col_count);

    int tmp;
    for (int i = 0; i < row_count * col_count; ++i) {
        cin >> tmp;
        pathFinder.feed(tmp);
    }

    int qcount;
    cin >> qcount;
    Point start, end;
    for (int i = 0; i < qcount; ++i) {
        cin >> start.x >> start.y >> end.x >> end.y;
        cout << pathFinder.findShortestPath(start, end) << endl;
    }
    return 0;
}