/*******************************************************************/
/*                                                                 */
/*  A1 Part 3: Majority Element starter file                       */
/*                                                                 */
/*  Author1 Name: Tim Roberts		 							   */
/*      - majorityElement										   */
/*		- findCandidate											   */		                                            

	/*Author2 Name: Jared Cotton
		- review and bug-fixing of both majorityelement and findCandidate*/
/*                                                                 */
/*******************************************************************/

bool findCandidate(int array[],int& candidate, int sz);

//Returns true if there is an element that occurs greater than sz/2
//number of times
bool majorityelement(const int arr[], int& majority, int sz){

	int* copy = new int[sz];
	int count = 0;

	//copy array
	for (int i = 0; i < sz; ++i) {
		copy[i] = arr[i];
	}

	//find possible candidate
	if (findCandidate(copy, majority, sz)) {

		//verify candidate is majority
		for (int i = 0; i < sz; ++i)
			if (arr[i] == majority) ++count;
	}

	delete[] copy;
	return count > (sz / 2);
}

//Returns true if the supplied array has a potential majority element.
//Result to be confirmed by majorityElement
bool findCandidate(int array[],int& candidate, int sz){
	
	bool hasCandidate = false;
	int count = 0;
	int* oddCandidate = nullptr;

	if (sz == 1)
	{ 
		candidate = array[0];
		hasCandidate = true;
	}
	else 
	{
		for (int i = 0; i < sz; i += 2) {

			if (i == sz - 1); //do nothing if on last element of an odd sized array
			else if(array[i] == array[i + 1]) {
				array[count++] = array[i];
			}
		}

		if ((sz % 2)) {
			oddCandidate = new int(array[sz - 1]);
		}

		if (count != 0) {
			hasCandidate = findCandidate(array, candidate, count);
		}

		//if no candidate found, see if oddCandidate availible
		if (!hasCandidate && oddCandidate != nullptr)
		{
			candidate = *oddCandidate;
			hasCandidate = true;
		}
	}

	delete oddCandidate;
	return hasCandidate;
}


//author: Jay Cotton
//custom made tester of examples from wiki
//int main()
//{
//	int candidate;
//	bool result;
//
//	int arr1[22] = { 5,5, 5,5, 3,2 ,5,5, 5,5, 6,6, 7,7, 6,6, 8,8, 8,8, 5,5 };
//	int arr2[22] = { 5,5, 5,5, 3,2 ,5,5, 4,5, 6,6, 7,7, 6,6, 8,8, 8,8, 5,5 };
//	int arr3[22] = { 5,1, 5,5, 3,2 ,4,5, 4,5, 6,6, 7,7, 6,6, 8,8, 8,8, 5,5 };
//	int arr4[22] = { 1,1, 1,1, 2,2, 2,2, 3,3, 3,3, 3,3, 15,16, 17,18, 19,20, 21,22 };
//
//	result = findCandidate(arr1, candidate, 22);
//
//	std::cout << "arr1: result = " << result << " | candidate = " << candidate << std::endl;
//
//	result = findCandidate(arr2, candidate, 22);
//
//	std::cout << "arr2: result = " << result << " | candidate = " << candidate << std::endl;
//
//	result = findCandidate(arr3, candidate, 22);
//
//	std::cout << "arr3: result = " << result << " | candidate = " << candidate << std::endl;
//
//	result = findCandidate(arr4, candidate, 22);
//
//	std::cout << "arr4: result = " << result << " | candidate = " << candidate << std::endl;
//
//	return 0;
//}