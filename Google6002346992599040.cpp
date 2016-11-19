#include <iostream>
#include <list>
using namespace std;

/*  Implement method:

Lìst<Range> getRanges(Lìst<Shard> shards, Lìst<Key> keys)
That returns list of ranges. Each range represents multiple keys aggregated over a shard:
n-keys —> 1-shard —> l-range

Method should return no more than 1 range per shard that spans all keys or their parts belonging to this shard.

Each of the ‘Range` , 'Shard’ and ‘Key’ classes have ‘end’ and ‘start’ fields of int type, where ‘start’ is inclusive and ‘end’ is exclusive.

Ex:         1—9, 12—59, 100—999         <— shards   (input)
            2—3, 6—8, 11—20, 200—220    <— keys     (input)
            2—8, 12—20, 200—220         <— ranges   (output)

Complexity: O(m+n)  no. of shards + no. of keys                                                                                                                                                                                                                     */


class Interval
{
public:
    int s, e;

    Interval(int start, int end) : s(start), e(end) {}
};

list<Interval> getRanges(list<Interval>& shards, list<Interval>& keys)
{
    list<Interval> res;

    auto kit = keys.begin();

    for (auto sit = shards.begin(); sit != shards.end(); sit++)
    {
        Interval *merge = NULL;

        for (;kit != keys.end(); kit++)
        {
            if ( (*kit).e < (*sit).s )
                continue;
            else if ( (*sit).e < (*kit).s )
                break;
            else
            {
                if (!merge)
                    merge = new Interval(max((*kit).s, (*sit).s),  min((*kit).e, (*sit).e));
                else
                    merge->e = max(merge->e, min((*kit).e, (*sit).e));
            }

            if ((*kit).e > (*sit).e)    // if key crosses the boundary of the shard, it might be part of the next shard, so dont increment  (partial overlap)
                break;
        }

        if (merge)                      // this is be outside the inner for loop    Ex: shard<100, 999>     keys<200, 220>
            res.push_back(*merge);
    }

    return res;
}

int main()
{
    list<Interval> shards = {Interval(1, 9), Interval(12, 59), Interval(100, 999)};
    list<Interval> keys = {Interval(2, 3), Interval(6, 8), Interval(11, 20), Interval(200, 220)};
    // list<Interval> keys = {Interval(2, 3), Interval(6, 8), Interval(8, 20), Interval(200, 220)};

    list<Interval> ranges = getRanges(shards, keys);

    for (auto it = ranges.begin(); it != ranges.end(); it++)
        cout << (*it).s << "-" << (*it).e << ", ";
    cout << endl;

    return 0;
}
