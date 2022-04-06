*temp = head, *ans = head
K = 1, target = 0 // target = the number of floor(2K/5)
while(temp != NULL)
    temp = temp -> next
    K++
    // if target != floor(2K/5), update target and ans
    if(target != floor(2*K / 5)
        target = floor(2*K / 5)
        // since floor(2K/5) is sequentially 2, 4, 6, 8, 10..., and ans start from head (node 1)
        // ans = ans -> next if ans is now node 1
        if(target == 2)
            ans = ans -> next
        else
            ans = ans -> next -> next
return ans -> data
