def LCS(s1,s2):
    l1=len(s1)
    l2=len(s2)
    #生成一个len(s1)+1*len(s2)+1横轴表示s2，纵轴表示s1，第0行，第0列表示边界，即一个子串已经消耗完
    lcs=[[0 for i in range(l2+1)] for j in range(l1+1)]
    flag=[[0 for i in range(l2+1)] for j in range(l1+1)]
    for i in range(l1):
        for j in range(l2):
            if s1[i]==s2[j]:
                lcs[i+1][j+1]=lcs[i][j]+1
                flag[i+1][j+1]='ok'
            else:
                if lcs[i][j+1]>=lcs[i+1][j]:
                    lcs[i+1][j+1]=lcs[i][j+1]
                    flag[i+1][j+1]='left'
                else:
                    lcs[i+1][j+1]=lcs[i+1][j]
                    flag[i+1][j+1]='up'
    return lcs,flag
#需要标志flag数组，字符串a，用于打印字符，i和j表示遍历的位置
def printLCS1(flag,a,i,j):
    if i==0 or j==0:
        return#递归返回条件
    if flag[i][j]=='ok':
        printLCS1(flag,a,i-1,j-1)
        print(a[i-1],end=',')#字符串与flag之间的下标差了一个1
    elif flag[i][j]=='up':
        printLCS1(flag,a,i,j-1)
    else:
        printLCS1(flag,a,i-1,j)

def printLCS2(lcs,a,i,j):
    if i==0 or j==0:
        return
    if lcs[i][j]==lcs[i-1][j-1]+1:
        printLCS2(lcs,a,i-1,j-1)
        print(a[i-1],end=',')
    elif lcs[i-1][j]>=lcs[i][j-1]:
        printLCS2(lcs,a,i-1,j)
    else:
        printLCS2(lcs,a,i,j-1 )

def printLCS3(lcs,l1,l2):
    i=l1;j=l2
    lcsPath=[]
    while(i!=0 and j!=0):
        if lcs[i][j]==lcs[i-1][j-1]+1:
            lcsPath.append(a[i-1])
            i-=1;j-=1
        elif lcs[i-1][j]>=lcs[i][j-1]:
             i-=1
        else:
            j-=1
    lcsPath.reverse()
    return lcsPath
setOfLCS=[]

def printLCS4(lcs,l1,l2,a,b,lcsPath):
    i=l1;j=l2
    while(i>0 and j>0):
        #if  lcs[i][j]==lcs[i-1][j-1]+1:#这个不可以作为判断条件
             #print("a[i-1]==b[j-1],{}=={}".format(a[i-1],b[j-1]))
        if  a[i-1]==b[j-1]:
             lcsPath.append(a[i-1])
             i-=1;j-=1
        elif lcs[i-1][j]>lcs[i][j-1]:
             i-=1
        elif lcs[i-1][j]<lcs[i][j-1]:
             j-=1
        else:
            printLCS4(lcs, i, j-1, a,b, lcsPath.copy())
            printLCS4(lcs,i-1,j,a,b,lcsPath.copy())
            return#?
    lcsPath.reverse()
    if lcsPath not in setOfLCS:
       setOfLCS.append(lcsPath)


if __name__ == '__main__':
    a = 'ABCBDAB'
    b = 'BDCABA'
    #b='MNHJKL'
    lcs,flag=LCS(a,b)
    for item in lcs:
        print(item)
    print('=================================')
    for item in flag:
        print(item)
    printLCS4(lcs,len(a),len(b),a,b,[])
    if  setOfLCS[0]:
        print('There are {} longest common subsequence exists in the two sequences given above'.format(len(setOfLCS)))
        for subseq in setOfLCS:
            for elem in subseq:
                print(elem,end='')
            print()
    else:
        print('The Longest common Subsequence does not exist')
