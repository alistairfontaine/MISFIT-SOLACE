mergeInto(LibraryManager.library, {
    _stdin_getchar: function() {
        if (typeof window !== 'undefined' && window.misfitInputQueue && window.misfitInputQueue.length > 0) {
            return window.misfitInputQueue.shift();
        }
        return 0;
    }
});

