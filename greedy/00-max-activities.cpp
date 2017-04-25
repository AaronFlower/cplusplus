#include <iostream>
#include <algorithm>

using namespace std;

struct Activity {
    int start;
    int end;
};
/**
 * 获取可执行的最大进行数。
 */
int getMaxActivities(Activity * & acts, int len)
{
    int prevEnd = -1;
    int count = 0;
    for (int i = 0; i < len; ++i)
    {
        if (acts[i].start > prevEnd) {
            ++ count;
            prevEnd = acts[i].end;
        }
    }
    return count;
}

int main() {
    int numTests, numActivities;
    int i = 0, k = 0;
    Activity *activities;
    cin >> numTests;
    while(i++ < numTests) {
        cin>>numActivities;
        activities = new Activity[numActivities];
        for (k = 0; k < numActivities; ++k) {
            cin >> activities[k].start;
        }
        for (k =0; k < numActivities; ++k) {
            cin >> activities[k].end;
        }
        // Ascending sort by end time;
        sort(activities, activities + numActivities, [](Activity a1, Activity a2){
            return a1.end < a2.end;
        });
        for (k = 0; k < numActivities; ++k)
        {
            cout << "[" << activities[k].start << "," << activities[k].end <<"]" << "\t";
        }
        cout << endl;
        cout << "The count is :" << getMaxActivities(activities, numActivities) << endl;
        delete [] activities;
    }
    cout << endl;
	return 0;
}