// bool horiz/vert scrollbars

/*
    auto-hide scroll bars?
        content rectangle is calculated during alignment..
        so we don't know f we need them until after alignment,
        and if so, child widgets might need realignment again to fit a smaller
        content rect (because of the aded scrollbars)..
*/
