line 51:
    lazy_if<is_same<float, double>, identity<int>, identity<short> >::type
    instantiates:
    - line 14: 
        lazy_if_c<is_same<float, double>::value, identity<int>, identity<short> >::type
        instantiates:
            - line 43:
                is_same<float, double>
                instantiates:
                    line 37:
                        bool_<false>
            - line 8:
                lazy_if_c<false, identity<int>, identity<short> >
                instantiates:
                    - line 32:
                        identity<short>

