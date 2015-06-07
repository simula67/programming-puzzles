int [] longestSubsequence(int []seq)
{
    if((seq.length == 1) || (seq.length==0)
    {
        return seq;
    }
    int [] tail = slice( seq );
    int tailLongest = longestSubSequence( tail );
    int head = seq[0]
    if( tail[0] > head ) {
        return appendHeadAndTail( head, tail );
    } else {
        return tail;
    }
}
int [] slice( int [] input)
{
    int [] result = new int[input.length-1];
    for(int i = 1;i<input.length;i++)
    {
        result[i-1] = input[i];
    }
    return result;
}
int [] appendHeadAndTail( int head, int[] tail )
{
    int [] result = new int[tail.length+1];
    result[0] = head;
    for(int i = 1;i<tail.length;i++)
    {
        result[i] = tail[i-1];
    }
    return result;
}
int lengthOfLongestSubSequence( int []input )
{
    return longestSubsequence(input).length;
}
