class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int tar) {
        unordered_map<int, int> mp;
        
        for(int i = 0; i < nums.size(); i++)
        {
            if(mp.find(tar - nums[i]) != mp.end())
                return {mp[tar - nums[i]], i};
            
            mp[nums[i]] = i;
        }
        return {};
    }
};
