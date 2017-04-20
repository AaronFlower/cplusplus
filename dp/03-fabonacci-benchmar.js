console.time('FabDp')
// Overlapping Subproblems
function fabDp(n) {
	var fabArr = []
	fabArr[0] = 1
	fabArr[1] = 1
	for (let i = 2; i <= n; ++i ) {
		fabArr[i] = fabArr[0] + fabArr[1]
	}
	return fabArr[n];
}
console.log(fabDp(10000))
console.timeEnd('FabDp')

console.time('Fab')
function fab(n) {
	if (n <= 1) {
		return 1
	} else {
		return fab(n-1) + fab(n - 2)
	}
}
console.log(fab(1000))
console.timeEnd('Fab')

/**
 * 
 *	Longest Increasing subsequence
 * For example, the length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is {10, 22, 33, 50, 60, 80}.
 */


arr = [10, 22, 9, 33, 21, 50, 41, 60, 80]
/* Initialize LIS values for all indexes , memory Initialize*/
lis = Array.from(arr, () => 1)
 /* Compute optimized LIS values in bottom up manner */
for(i = 1; i< 11; ++i){
    for (j = 0; j < 11; ++j) {
        if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
            lis[i] = lis[j] + 1
        }
    }
}
console.log(Math.max(...lis))