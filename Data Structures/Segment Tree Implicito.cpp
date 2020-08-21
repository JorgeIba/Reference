//18
void update(Node *id, int l, int r, int begin, int end, int value)
{
    if(end < l || r < begin) return;
    if(begin <= l && r <= end) id->value = value;
    else{
        int mid = l + ((r-l)>>1);
        if(begin <= mid){
            extendIzq(id);
            update(id->izq, l, mid, begin, end, value );
        }
        else{
            extendDer(id);
            update(id->der, mid + 1, r, begin, end, value);
        }
        id->value = (id->izq != NULL? id->izq->value: 0) + (id->der != NULL? id->der->value: 0);
    }
}
//16
lli query(Node *id, int l, int r, int begin, int end)
{
    if( end < l || r < begin) return 0;

    if(begin <= l && r<= end) return id->value;
    else{
        lli res = 0;
        int mid = l + ((r-l)>>1);
        if(l<=mid)
            res += id->izq!=NULL?query(id->izq, l, mid, begin, end):0;
        if(r>mid)
            res += id->der!=NULL?query(id->der, mid+1, r, begin, end):0;
        return res;
    }
}