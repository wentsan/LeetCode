double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int totalSize = nums1Size + nums2Size;
    int con[totalSize];
    int mid = 0, i = 0, j = 0, pos = 0;
    int state = 0;
    double r;

    if (totalSize % 2){
        mid = (totalSize - 1) / 2;
    } else {
        mid = totalSize / 2;
        state = 1;
    }


    while (i < nums1Size && j < nums2Size){
        if (*(nums1+i) < *(nums2+j)){
            con[pos++] = *(nums1+i);
            i++;
        } else if (*(nums1+i) == *(nums2+j)){
            con[pos++] = con[pos++] = *(nums1+i);
            i++;
            j++;
        }else {
            con[pos++] = *(nums2+j);
            j++;
        }
    }

    while(i < nums1Size){
        con[pos++] = *(nums1+i);
        i++;
    }

    while(j < nums2Size){
        con[pos++] = *(nums2+j);
        j++;
    }

    if (state){
            r = ((double) con[mid] + (double) con[mid-1]) / 2;
        } else {
            r = (double) con[mid];
    }

    return r;
}