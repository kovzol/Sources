#include "mod2.h"
#include "structs.h"
#include "polys.h"
#include <Minor.h>

void MinorKey::reset() {
    _numberOfRowBlocks = 0;
    _numberOfColumnBlocks = 0;
    delete [] _rowKey;
    delete [] _columnKey;
    _rowKey = 0;
    _columnKey = 0;
}

MinorKey::MinorKey (const MinorKey& mk) {
    _numberOfRowBlocks = mk.getNumberOfRowBlocks();
    _numberOfColumnBlocks = mk.getNumberOfColumnBlocks();;

    // allocate memory for new entries in _rowKey and _columnKey;
    _rowKey = new unsigned long[_numberOfRowBlocks];
    _columnKey = new unsigned long[_numberOfColumnBlocks];

    // copying values from parameter arrays to private arrays
    for (int r = 0; r < _numberOfRowBlocks; r++)
        _rowKey[r] = mk.getRowKey(r);
    for (int c = 0; c < _numberOfColumnBlocks; c++)
        _columnKey[c] = mk.getColumnKey(c);
}

// just to make the compiler happy;
// this method should never be called
MinorKey& MinorKey::operator=(const MinorKey&) {
    assert(false);
    return *this;
}

void MinorKey::set(const int lengthOfRowArray, const unsigned long* rowKey,
                   const int lengthOfColumnArray, const unsigned long* columnKey) {
    // free memory of _rowKey and _columnKey
    if (_numberOfRowBlocks > 0) { delete [] _rowKey; }
    if (_numberOfColumnBlocks > 0) { delete [] _columnKey; }

    _numberOfRowBlocks = lengthOfRowArray;
    _numberOfColumnBlocks = lengthOfColumnArray;

    // allocate memory for new entries in _rowKey and _columnKey;
    _rowKey = new unsigned long[_numberOfRowBlocks];
    _columnKey = new unsigned long[_numberOfColumnBlocks];

    // copying values from parameter arrays to private arrays
    for (int r = 0; r < _numberOfRowBlocks; r++)
        _rowKey[r] = rowKey[r];
    for (int c = 0; c < _numberOfColumnBlocks; c++)
        _columnKey[c] = columnKey[c];
}

MinorKey::MinorKey(const int lengthOfRowArray, const unsigned long* const rowKey,
                   const int lengthOfColumnArray, const unsigned long* const columnKey) {
    _numberOfRowBlocks = lengthOfRowArray;
    _numberOfColumnBlocks = lengthOfColumnArray;

    // allocate memory for new entries in _rowKey and _columnKey;
    _rowKey = new unsigned long[_numberOfRowBlocks];
    _columnKey = new unsigned long[_numberOfColumnBlocks];
    assert(_rowKey != rowKey);
    assert(_columnKey != rowKey);
    assert(_rowKey != columnKey);
    assert(_columnKey != columnKey);

    // copying values from parameter arrays to private arrays
    for (int r = 0; r < _numberOfRowBlocks; r++)
        _rowKey[r] = rowKey[r];

    for (int c = 0; c < _numberOfColumnBlocks; c++)
        _columnKey[c] = columnKey[c];
}

MinorKey::~MinorKey() {
    // free memory of _rowKey and _columnKey
    delete [] _rowKey;
    delete [] _columnKey;
}

void MinorKey::print() const {
    cout << this->toString();
}

int MinorKey::getAbsoluteRowIndex(const int i) const {
    // This method is to return the absolute (0-based) index of the i-th row encoded in \a this.
    // Example: bit-pattern of rows: "10010001101", i = 3:
    //    This should yield the 0-based absolute index of the 3-rd bit (counted from the right), i.e. 7.

    int matchedBits = -1; // counter for matched bits; this needs to reach i, then we're done
    for (int block = 0; block < getNumberOfRowBlocks(); block ++) { // start with lowest bits, i.e. in block No. 0
        unsigned long blockBits = getRowKey(block); // the bits in this block of 32 bits
        unsigned long shiftedBit = 1;
        int exponent = 0;
        // The invariant "shiftedBit = 2^exponent" will hold throughout the entire while loop.
        while (exponent < 32) {
            if (shiftedBit & blockBits) matchedBits++;
            if (matchedBits == i) return exponent + (32 * block);
            shiftedBit = shiftedBit << 1;
            exponent++;
        }
    }
    // We should never reach this line of code.
    assert(false);
}

int MinorKey::getAbsoluteColumnIndex(const int i) const {
    // This method is to return the absolute (0-based) index of the i-th column encoded in \a this.
    // Example: bit-pattern of columns: "10010001101", i = 3:
    //    This should yield the 0-based absolute index of the 3-rd bit (counted from the right), i.e. 7.

    int matchedBits = -1; // counter for matched bits; this needs to reach i, then we're done
    for (int block = 0; block < getNumberOfColumnBlocks(); block ++) { // start with lowest bits, i.e. in block No. 0
        unsigned long blockBits = getColumnKey(block); // the bits in this block of 32 bits
        unsigned long shiftedBit = 1;
        int exponent = 0;
        // The invariant "shiftedBit = 2^exponent" will hold throughout the entire while loop.
        while (exponent < 32) {
            if (shiftedBit & blockBits) matchedBits++;
            if (matchedBits == i) return exponent + (32 * block);
            shiftedBit = shiftedBit << 1;
            exponent++;
        }
    }
    // We should never reach this line of code.
    assert(false);
}

void MinorKey::getAbsoluteRowIndices(int* const target) const {
    int i = 0; // index for filling the target array
    for (int block = 0; block < getNumberOfRowBlocks(); block ++) { // start with lowest bits, i.e. in block No. 0
        unsigned long blockBits = getRowKey(block); // the bits in this block of 32 bits
        unsigned long shiftedBit = 1;
        int exponent = 0;
        // The invariant "shiftedBit = 2^exponent" will hold throughout the entire while loop.
        while (exponent < 32) {
            if (shiftedBit & blockBits) target[i++] = exponent + (32 * block);
            shiftedBit = shiftedBit << 1;
            exponent++;
        }
    }
    return;
}

void MinorKey::getAbsoluteColumnIndices(int* const target) const {
    int i = 0; // index for filling the target array
    for (int block = 0; block < getNumberOfColumnBlocks(); block ++) { // start with lowest bits, i.e. in block No. 0
        unsigned long blockBits = getColumnKey(block); // the bits in this block of 32 bits
        unsigned long shiftedBit = 1;
        int exponent = 0;
        // The invariant "shiftedBit = 2^exponent" will hold throughout the entire while loop.
        while (exponent < 32) {
            if (shiftedBit & blockBits) target[i++] = exponent + (32 * block);
            shiftedBit = shiftedBit << 1;
            exponent++;
        }
    }
    return;
}

int MinorKey::getRelativeRowIndex(const int i) const {
    // This method is to return the relative (0-based) index of the row with absolute index \c i.
    // Example: bit-pattern of rows: "10010001101", i = 7:
    //    This should yield the 0-based relative index of the bit corresponding to row no. 7,
    //    i.e. 3.

    int matchedBits = -1; // counter for matched bits; this is going to contain our return value
    for (int block = 0; block < getNumberOfRowBlocks(); block ++) { // start with lowest bits, i.e. in block No. 0
        unsigned long blockBits = getRowKey(block); // the bits in this block of 32 bits
        unsigned long shiftedBit = 1;
        int exponent = 0;
        // The invariant "shiftedBit = 2^exponent" will hold throughout the entire while loop.
        while (exponent < 32) {
            if (shiftedBit & blockBits) matchedBits++;
            if (exponent + (32 * block) == i) return matchedBits;
            shiftedBit = shiftedBit << 1;
            exponent++;
        }
    }
    // We should never reach this line of code.
    assert(false);
}

int MinorKey::getRelativeColumnIndex(const int i) const {
    // This method is to return the relative (0-based) index of the column with absolute index \c i.
    // Example: bit-pattern of columns: "10010001101", i = 7:
    //    This should yield the 0-based relative index of the bit corresponding to column no. 7,
    //    i.e. 3.

    int matchedBits = -1; // counter for matched bits; this is going to contain our return value
    for (int block = 0; block < getNumberOfColumnBlocks(); block ++) { // start with lowest bits, i.e. in block No. 0
        unsigned long blockBits = getColumnKey(block); // the bits in this block of 32 bits
        unsigned long shiftedBit = 1;
        int exponent = 0;
        // The invariant "shiftedBit = 2^exponent" will hold throughout the entire while loop.
        while (exponent < 32) {
            if (shiftedBit & blockBits) matchedBits++;
            if (exponent + (32 * block) == i) return matchedBits;
            shiftedBit = shiftedBit << 1;
            exponent++;
        }
    }
    // We should never reach this line of code.
    assert(false);
}

unsigned long MinorKey::getRowKey(const int blockIndex) const {
    return _rowKey[blockIndex];
}

unsigned long MinorKey::getColumnKey(const int blockIndex) const {
    return _columnKey[blockIndex];
}

int MinorKey::getNumberOfRowBlocks() const {
    return _numberOfRowBlocks;
}

int MinorKey::getNumberOfColumnBlocks() const {
    return _numberOfColumnBlocks;
}

int MinorKey::getSetBits(const int a) const {
    int b = 0;
    if (a == 1) { // rows
        for (int i = 0; i < _numberOfRowBlocks; i++) {
            unsigned long m = _rowKey[i];
            unsigned long k = 1;
            for (int j = 0; j < 32; j++) {
                // k = 2^j
                if (m & k) b++;
                k = k << 1;
            }
        }
    }
    else { // columns
        for (int i = 0; i < _numberOfColumnBlocks; i++) {
            unsigned long m = _columnKey[i];
            unsigned long k = 1;
            for (int j = 0; j < 32; j++) {
                // k = 2^j
                if (m & k) b++;
                k = k << 1;
            }
        }
    }
    return b;
}

MinorKey MinorKey::getSubMinorKey (const int absoluteEraseRowIndex,
                                   const int absoluteEraseColumnIndex) const {
    int rowBlock = absoluteEraseRowIndex / 32;
    int exponent = absoluteEraseRowIndex % 32;
    unsigned long newRowBits = getRowKey(rowBlock) - (1 << exponent);
    int highestRowBlock = getNumberOfRowBlocks() - 1;
    // highestRowBlock will finally contain the highest block index with non-zero bit pattern
    if ((newRowBits == 0) && (rowBlock == highestRowBlock)) {
        // we have thus nullified the highest block;
        // we can now forget about the highest block...
        highestRowBlock -= 1;
        while (getRowKey(highestRowBlock) == 0) // ...and maybe even some more zero-blocks
            highestRowBlock -= 1;
    }
    // highestRowBlock now contains the highest row block index with non-zero bit pattern

    int columnBlock = absoluteEraseColumnIndex / 32;
    exponent = absoluteEraseColumnIndex % 32;
    unsigned long newColumnBits = getColumnKey(columnBlock) - (1 << exponent);
    int highestColumnBlock = getNumberOfColumnBlocks() - 1;
    // highestColumnBlock will finally contain the highest block index with non-zero bit pattern
    if ((newColumnBits == 0) && (columnBlock == highestColumnBlock)) {
        // we have thus nullified the highest block;
        // we can now forget about the highest block...
        highestColumnBlock -= 1;
        while (getColumnKey(highestColumnBlock) == 0) // ...and maybe even some more zero-blocks
            highestColumnBlock -= 1;
    }
    // highestColumnBlock now contains the highest column block index with non-zero bit pattern

    MinorKey result(highestRowBlock + 1, _rowKey, highestColumnBlock + 1, _columnKey);
    // This is just a copy with maybe some leading bit blocks omitted. We still need to re-define
    // the row block at index 'rowBlock' and the column block at index 'columnBlock':
    if ((newRowBits != 0) || (rowBlock < getNumberOfRowBlocks() - 1)) result.setRowKey(rowBlock, newRowBits);
    if ((newColumnBits != 0) || (columnBlock < getNumberOfColumnBlocks() - 1)) result.setColumnKey(columnBlock, newColumnBits);

    if (result.getSetBits(1) != result.getSetBits(2)) { // asserts that the number of selected rows and columns are equal
        cout << endl;
        this->print();
        cout << endl;
        result.print();
        cout << endl;
        cout << "rows: " << result.getSetBits(1) << " / columns: " << result.getSetBits(2);
        cout << endl;
        cout << "row to be erased: " << absoluteEraseRowIndex << " / column to be erased: " << absoluteEraseColumnIndex << endl;
        assert(false);
    }

    return result;
}

void MinorKey::setRowKey (const int blockIndex, const unsigned long rowKey) {
    _rowKey[blockIndex] = rowKey;
}

void MinorKey::setColumnKey (const int blockIndex, const unsigned long columnKey) {
    _columnKey[blockIndex] = columnKey;
}

int MinorKey::compare (const MinorKey& that) const {
    // compare by rowKeys first; in case of equality, use columnKeys
    if (this->getNumberOfRowBlocks() < that.getNumberOfRowBlocks())
        return -1;
    if (this->getNumberOfRowBlocks() > that.getNumberOfRowBlocks())
        return 1;
    // Here, numbers of rows are equal.
    for (int r = this->getNumberOfRowBlocks() - 1; r >= 0; r--) {
        if (this->getRowKey(r) < that.getRowKey(r)) return -1;
        if (this->getRowKey(r) > that.getRowKey(r)) return 1;
    }
    // Here, this and that encode ecaxtly the same sets of rows.
    // Now, we take a look at the columns.
    if (this->getNumberOfColumnBlocks() < that.getNumberOfColumnBlocks())
        return -1;
    if (this->getNumberOfColumnBlocks() > that.getNumberOfColumnBlocks())
        return 1;
    // Here, numbers of columns are equal.
    for (int c = this->getNumberOfColumnBlocks() - 1; c >= 0; c--) {
        if (this->getColumnKey(c) < that.getColumnKey(c)) return -1;
        if (this->getColumnKey(c) > that.getColumnKey(c)) return 1;
    }
    // Here, this and that encode exactly the same sets of rows and columns.
    return 0;
}

// just to make the compiler happy;
// this method should never be called
bool MinorKey::operator==(const MinorKey& mk) const {
    assert(false);
    return this->compare(mk) == 0;
}

// just to make the compiler happy;
// this method should never be called
bool MinorKey::operator<(const MinorKey& mk) const {
    assert(false);
    return this->compare(mk) == -1;
}

void MinorKey::selectFirstRows (const int k, const MinorKey& mk) {
    int hitBits = 0;      // the number of bits we have hit; in the end, this has to be equal to k,
                          // the dimension of the minor
    int blockIndex = -1;  // the index of the current long in mk
    unsigned long highestLong = 0;  // the new highest block of this MinorKey
    // We determine which longs of mk we can copy. Their indices will be 0, 1, ..., blockIndex - 1.
    // And highestLong is going to capture the highest long (which may be only a portion of
    // the corresponding long in mk. We loop until hitBits = k:
    while (hitBits < k) {
        blockIndex++;
        highestLong = 0;
        unsigned long currentLong = mk.getRowKey(blockIndex);
        unsigned long shiftedBit = 1;
        int exponent = 0;
        // invariant in the loop: shiftedBit = 2^exponent
        while (exponent < 32 && hitBits < k) {
            if (shiftedBit & currentLong) {
                highestLong += shiftedBit;
                hitBits++;
            }
            shiftedBit = shiftedBit << 1;
            exponent++;
        }
    }
    // free old memory
    delete [] _rowKey; _rowKey = 0;
    _numberOfRowBlocks = blockIndex + 1;
    // allocate memory for new entries in _rowKey;
    _rowKey = new unsigned long[_numberOfRowBlocks];
    // copying values from mk to this MinorKey
    for (int r = 0; r < blockIndex; r++)
        _rowKey[r] = mk.getRowKey(r);
    _rowKey[blockIndex] = highestLong;
}

void MinorKey::selectFirstColumns (const int k, const MinorKey& mk) {
    int hitBits = 0;      // the number of bits we have hit; in the end, this has to be equal to k,
                          // the dimension of the minor
    int blockIndex = -1;  // the index of the current long in mk
    unsigned long highestLong = 0;  // the new highest block of this MinorKey
    // We determine which longs of mk we can copy. Their indices will be 0, 1, ..., blockIndex - 1.
    // And highestLong is going to capture the highest long (which may be only a portion of
    // the corresponding long in mk. We loop until hitBits = k:
    while (hitBits < k) {
        blockIndex++;
        highestLong = 0;
        unsigned long currentLong = mk.getColumnKey(blockIndex);
        unsigned long shiftedBit = 1;
        int exponent = 0;
        // invariant in the loop: shiftedBit = 2^exponent
        while (exponent < 32 && hitBits < k) {
            if (shiftedBit & currentLong) {
                highestLong += shiftedBit;
                hitBits++;
            }
            shiftedBit = shiftedBit << 1;
            exponent++;
        }
    }
    // free old memory
    delete [] _columnKey; _columnKey = 0;
    _numberOfColumnBlocks = blockIndex + 1;
    // allocate memory for new entries in _columnKey;
    _columnKey = new unsigned long[_numberOfColumnBlocks];
    // copying values from mk to this MinorKey
    for (int c = 0; c < blockIndex; c++)
        _columnKey[c] = mk.getColumnKey(c);
    _columnKey[blockIndex] = highestLong;
}

bool MinorKey::selectNextRows (const int k, const MinorKey& mk) {
    // We need to compute the set of k rows which must all be contained in mk.
    // AND: This set must be the least possible of this kind which is larger
    //      than the currently encoded set of rows. (Here, '<' is w.r.t. to the natural
    //       ordering on multi-indices.
    // Example: mk encodes the rows according to the bit pattern 11010111, k = 3, this
    //          MinorKey encodes 10010100. Then, the method must shift the set of rows in
    //          this MinorKey to 11000001 (, and return true).

    // The next two variables will finally name a row which is
    // (1) currently not yet among the rows in this MinorKey, but
    // (2) among the rows in mk, and
    // (3) which is "higher" than the lowest row in this MinorKey, and
    // (4) which is the lowest possible choice such that (1) - (3) hold.
    // If we should not be able to find such a row, then there is no next subset of rows.
    // In this case, the method will return false; otherwise always true.
    int newBitBlockIndex = 0;         // the block index of the bit
    unsigned long newBitToBeSet = 0;  // the bit as 2^e, where 0 <= e <= 31

    int blockCount = this->getNumberOfRowBlocks();  // number of longs (representing rows) in this MinorKey
    int mkBlockIndex = mk.getNumberOfRowBlocks();   // for iterating along the blocks of mk

    int hitBits = 0;    // the number of bits we have hit
    int bitCounter = 0; // for storing the number of bits hit before a specific moment; see below

    while (hitBits < k) {
        mkBlockIndex--;
        unsigned long currentLong = mk.getRowKey(mkBlockIndex);
        unsigned long shiftedBit = 1 << 31; // initially, this equals 2^31, i.e. the highest bit
        while (hitBits < k && shiftedBit > 0) {
            if (blockCount - 1 >= mkBlockIndex &&
                shiftedBit & this->getRowKey(mkBlockIndex)) hitBits++;
            else if (shiftedBit & currentLong) {
                newBitToBeSet = shiftedBit;
                newBitBlockIndex = mkBlockIndex;
                bitCounter = hitBits; // So, whenever we set newBitToBeSet, we want to remember the momentary
                                      // number of hit bits. This will later be needed; see below.
            }
            shiftedBit = shiftedBit >> 1;
        }
    }

    if (newBitToBeSet == 0) {
        return false;
    }
    else {
        // Note that the following must hold when reaching this line of code:
        // (1) The row with bit newBitToBeSet in this->getRowKey(newBitBlockIndex) is currently
        //     not among the rows in this MinorKey, but
        // (2) it is among the rows in mk, and
        // (3) it is higher than the lowest row in this MinorKey, and
        // (4) it is the lowest possible choice such that (1) - (3) hold.
        // In the above example, we would reach this line with
        // newBitToBeSet == 2^6 and bitCounter == 1 (resulting from the bit 2^7).

        if (blockCount - 1 < newBitBlockIndex) { // In this case, _rowKey is to small.
            // free old memory
            delete [] _rowKey; _rowKey = 0;
            _numberOfRowBlocks = newBitBlockIndex + 1;
            // allocate memory for new entries in _rowKey;
            _rowKey = new unsigned long[_numberOfRowBlocks];
        }
        else {
            // We need to delete all bits in _rowKey[newBitBlockIndex] that are below newBitToBeSet:
            unsigned long aLong = this->getRowKey(newBitBlockIndex);
            unsigned long deleteBit = newBitToBeSet >> 1; // in example: = 2^5
            while (deleteBit > 0) {
                if (aLong & deleteBit) aLong -= deleteBit;
                deleteBit = deleteBit >> 1;
            };
            _rowKey[newBitBlockIndex] = aLong;
            // ...and we delete all entries in _rowKey[i] for 0 <= i < newBitBlockIndex
            for (int i = 0; i < newBitBlockIndex; i++)
                _rowKey[i] = 0;
        }

        // We have now deleted all bits from _rowKey[...] below the bit 2^newBitToBeSet.
        // In the example we shall have at this point: _rowKey[...] = 10000000.
        // Now let's set the new bit:
        _rowKey[newBitBlockIndex] += newBitToBeSet; // _rowKey[newBitBlockIndex] = 11000000
        bitCounter++; // This is now the number of correct bits in _rowKey[...]; i.e. in the
                      // example this will be equal to 2.

        // Now we only need to fill _rowKey[...] with the lowest possible bits until it
        // consists of exactly k bits. (We know that we need to set exactly (k - bitCounter)
        // additional bits.)
        mkBlockIndex = -1;
        while (bitCounter < k) {
            mkBlockIndex++;
            unsigned long currentLong = mk.getRowKey(mkBlockIndex);
            unsigned long shiftedBit = 1;
            int exponent = 0;
            // invariant: shiftedBit = 2^exponent
            while (bitCounter < k && exponent < 32) {
                if (shiftedBit & currentLong) {
                    _rowKey[mkBlockIndex] += shiftedBit;
                    bitCounter++;
                };
                shiftedBit = shiftedBit << 1;
                exponent++;
            }
        };
        // in the example, we shall obtain _rowKey[...] = 11000001

        return true;
    }
}

bool MinorKey::selectNextColumns (const int k, const MinorKey& mk) {
    // We need to compute the set of k columns which must all be contained in mk.
    // AND: This set must be the least possible of this kind which is larger
    //      than the currently encoded set of columns. (Here, '<' is w.r.t. to the natural
    //       ordering on multi-indices.
    // Example: mk encodes the columns according to the bit pattern 11010111, k = 3, this
    //          MinorKey encodes 10010100. Then, the method must shift the set of columns in
    //          this MinorKey to 11000001 (, and return true).

    // The next two variables will finally name a columns which is
    // (1) currently not yet among the columns in this MinorKey, but
    // (2) among the columns in mk, and
    // (3) which is "higher" than the lowest columns in this MinorKey, and
    // (4) which is the lowest possible choice such that (1) - (3) hold.
    // If we should not be able to find such a columns, then there is no next subset of columns.
    // In this case, the method will return false; otherwise always true.
    int newBitBlockIndex = 0;         // the block index of the bit
    unsigned long newBitToBeSet = 0;  // the bit as 2^e, where 0 <= e <= 31

    int blockCount = this->getNumberOfColumnBlocks();  // number of longs (representing columns) in this MinorKey
    int mkBlockIndex = mk.getNumberOfColumnBlocks();   // for iterating along the blocks of mk

    int hitBits = 0;    // the number of bits we have hit
    int bitCounter = 0; // for storing the number of bits hit before a specific moment; see below

    while (hitBits < k) {
        mkBlockIndex--;
        unsigned long currentLong = mk.getColumnKey(mkBlockIndex);
        unsigned long shiftedBit = 1 << 31; // initially, this equals 2^31, i.e. the highest bit
        while (hitBits < k && shiftedBit > 0) {
            if (blockCount - 1 >= mkBlockIndex &&
                shiftedBit & this->getColumnKey(mkBlockIndex)) hitBits++;
            else if (shiftedBit & currentLong) {
                newBitToBeSet = shiftedBit;
                newBitBlockIndex = mkBlockIndex;
                bitCounter = hitBits; // So, whenever we set newBitToBeSet, we want to remember the momentary
                                      // number of hit bits. This will later be needed; see below.
            }
            shiftedBit = shiftedBit >> 1;
        }
    }

    if (newBitToBeSet == 0) {
        return false;
    }
    else {
        // Note that the following must hold when reaching this line of code:
        // (1) The columns with bit newBitToBeSet in this->getColumnKey(newBitBlockIndex) is currently
        //     not among the columns in this MinorKey, but
        // (2) it is among the columns in mk, and
        // (3) it is higher than the lowest columns in this MinorKey, and
        // (4) it is the lowest possible choice such that (1) - (3) hold.
        // In the above example, we would reach this line with
        // newBitToBeSet == 2^6 and bitCounter == 1 (resulting from the bit 2^7).

        if (blockCount - 1 < newBitBlockIndex) { // In this case, _columnKey is to small.
            // free old memory
            delete [] _columnKey; _columnKey = 0;
            _numberOfColumnBlocks = newBitBlockIndex + 1;
            // allocate memory for new entries in _columnKey;
            _columnKey = new unsigned long[_numberOfColumnBlocks];
        }
        else {
            // We need to delete all bits in _columnKey[newBitBlockIndex] that are below newBitToBeSet:
            unsigned long aLong = this->getColumnKey(newBitBlockIndex);
            unsigned long deleteBit = newBitToBeSet >> 1; // in example: = 2^5
            while (deleteBit > 0) {
                if (aLong & deleteBit) aLong -= deleteBit;
                deleteBit = deleteBit >> 1;
            };
            _columnKey[newBitBlockIndex] = aLong;
            // ...and we delete all entries in _columnKey[i] for 0 <= i < newBitBlockIndex
            for (int i = 0; i < newBitBlockIndex; i++)
                _columnKey[i] = 0;
        }

        // We have now deleted all bits from _columnKey[...] below the bit 2^newBitToBeSet.
        // In the example we shall have at this point: _columnKey[...] = 10000000.
        // Now let's set the new bit:
        _columnKey[newBitBlockIndex] += newBitToBeSet; // _columnKey[newBitBlockIndex] = 11000000
        bitCounter++; // This is now the number of correct bits in _columnKey[...]; i.e. in the
                      // example this will be equal to 2.

        // Now we only need to fill _columnKey[...] with the lowest possible bits until it
        // consists of exactly k bits. (We know that we need to set exactly (k - bitCounter)
        // additional bits.)
        mkBlockIndex = -1;
        while (bitCounter < k) {
            mkBlockIndex++;
            unsigned long currentLong = mk.getColumnKey(mkBlockIndex);
            unsigned long shiftedBit = 1;
            int exponent = 0;
            // invariant: shiftedBit = 2^exponent
            while (bitCounter < k && exponent < 32) {
                if (shiftedBit & currentLong) {
                    _columnKey[mkBlockIndex] += shiftedBit;
                    bitCounter++;
                };
                shiftedBit = shiftedBit << 1;
                exponent++;
            }
        };
        // in the example, we shall obtain _columnKey[...] = 11000001

        return true;
    }
}

string MinorKey::toString() const {
    char h[32];
    string t = "";
    string s = "(";
    for (int r = this->getNumberOfRowBlocks() - 1; r >= 0; r--) {
        sprintf(h, "%ld", this->getRowKey(r)); t += h;
        if (r < this->getNumberOfRowBlocks() - 1)
            t = string(32 - t.length(), '0') + t;
        s += t;
    }
    s += ", ";
    for (int c = this->getNumberOfColumnBlocks() - 1; c >= 0; c--) {
        sprintf(h, "%ld", this->getColumnKey(c)); t += h;
        if (c < this->getNumberOfColumnBlocks() - 1)
            t = string(32 - t.length(), '0') + t;
        s += t;
    }
    s += ")";
    return s;
}

int MinorValue::_RankingStrategy = -1;

// just to make the compiler happy;
// this method should never be called
bool MinorValue::operator==(const MinorValue& mv) const {
    assert(false);
    return (this == &mv);  // compare addresses of both objects
}

// just to make the compiler happy;
// this method should never be called
bool MinorValue::operator<(const MinorValue& mv) const {
    assert(false);
    return (this < &mv);  // compare addresses of both objects
}

long MinorValue::getRetrievals() const {
    return _retrievals;
}

void MinorValue::incrementRetrievals() {
    _retrievals++;
}

long MinorValue::getPotentialRetrievals() const {
    return _potentialRetrievals;
}

long MinorValue::getMultiplications() const {
    return _multiplications;
}

long MinorValue::getSummations() const {
    return _summations;
}

long MinorValue::getAccumulatedMultiplications() const {
    return _accumulatedMult;
}

long MinorValue::getAccumulatedSummations() const {
    return _accumulatedSum;
}

void MinorValue::print() const {
    cout << this->toString();
}


void MinorValue::SetRankingStrategy(const int rankingStrategy) {
    _RankingStrategy = rankingStrategy;
    if (_RankingStrategy == 6) {
        // initialize the random generator with system time
        srand ( time(NULL) );
    }
}

int MinorValue::GetRankingStrategy() {
    return _RankingStrategy;
}

// this is for generically accessing the rank measure regardless of
// which strategy has been set
int MinorValue::getUtility () const {
    switch (this->GetRankingStrategy()) {
        case 1: return this->rankMeasure1();
        case 2: return this->rankMeasure2();
        case 3: return this->rankMeasure3();
        case 4: return this->rankMeasure4();
        case 5: return this->rankMeasure5();
        default: return this->rankMeasure1();
    }
}

// here are some sensible caching strategies:
int MinorValue::rankMeasure1 () const {
    // number of actually performed multiplications
    return this->getMultiplications();
}

int MinorValue::rankMeasure2 () const {
    // accumulated number of performed multiplications, i.e. all including nested multiplications
    return this->getAccumulatedMultiplications();
}

int MinorValue::rankMeasure3 () const {
    // number of performed multiplications, weighted with the ratio of
    // not yet performed retrievals over the maximal number of retrievals
    return this->getMultiplications() * (this->getPotentialRetrievals() - this->getRetrievals())
           / this->getPotentialRetrievals();
}

int MinorValue::rankMeasure4 () const {
    // number of performed multiplications,
    // multiplied with the number of not yet performed retrievals
    return this->getMultiplications() * (this->getPotentialRetrievals() - this->getRetrievals());
}

int MinorValue::rankMeasure5 () const {
    // number of not yet performed retrievals;
    // tends to cache entries longer when they are going to be retrieved more often in the future
    return this->getPotentialRetrievals() - this->getRetrievals();
}

int LongMinorValue::getWeight () const {
    // put measure for size of MinorValue here, i.e. number of monomials in polynomial;
    // so far, we use the accumulated number of multiplications (i.e., including all nested ones)
    // to simmulate the size of a polynomial
    return _accumulatedMult;
}

LongMinorValue::LongMinorValue (const long result, const int multiplications, const int summations,
                                const int accumulatedMultiplications, const int accumulatedSummations,
                                const int retrievals, const int potentialRetrievals) {
    _result = result;
    _multiplications = multiplications;
    _summations = summations;
    _accumulatedMult = accumulatedMultiplications;
    _accumulatedSum = accumulatedSummations;
    _potentialRetrievals = potentialRetrievals;
    _retrievals = retrievals;
}

LongMinorValue::LongMinorValue () {
    _result = -1;
    _multiplications = -1;
    _summations = -1;
    _accumulatedMult = -1;
    _accumulatedSum = -1;
    _potentialRetrievals = -1;
    _retrievals = -1;
}

LongMinorValue::~LongMinorValue()
{
}

long LongMinorValue::getResult() const {
    return _result;
}

string LongMinorValue::toString () const {
    char h[10];

    // Let's see whether a cache has been used to compute this MinorValue:
    bool cacheHasBeenUsed = true;
    if (this->getRetrievals() == -1) cacheHasBeenUsed = false;

    sprintf(h, "%ld", this->getResult());
    string s = h;
    s += " [retrievals: ";
    if (cacheHasBeenUsed) { sprintf(h, "%ld", this->getRetrievals()); s += h; }
    else s += "/";
    s += " (of ";
    if (cacheHasBeenUsed) { sprintf(h, "%ld", this->getPotentialRetrievals()); s += h; }
    else s += "/";
    s += "), *: ";
    sprintf(h, "%ld", this->getMultiplications()); s += h;
    s += " (accumulated: ";
    sprintf(h, "%ld", this->getAccumulatedMultiplications()); s += h;
    s += "), +: ";
    sprintf(h, "%ld", this->getSummations()); s += h;
    s += " (accumulated: ";
    sprintf(h, "%ld", this->getAccumulatedSummations()); s += h;
    s += "), weight: ";
    sprintf(h, "%d", this->getWeight()); s += h;
    s += ", rank: ";
    if (cacheHasBeenUsed) { sprintf(h, "%d", this->getUtility()); s += h; }
    else s += "/";
    s += "]";
    return s;
}

LongMinorValue::LongMinorValue (const LongMinorValue& mv) {
    _result = mv.getResult();
    _retrievals = mv.getRetrievals();
    _potentialRetrievals = mv.getPotentialRetrievals();
    _multiplications = mv.getMultiplications();
    _summations = mv.getSummations();
    _accumulatedMult = mv.getAccumulatedMultiplications();
    _accumulatedSum = mv.getAccumulatedSummations();
}

PolyMinorValue::PolyMinorValue (const poly result, const int multiplications, const int summations,
                                const int accumulatedMultiplications, const int accumulatedSummations,
                                const int retrievals, const int potentialRetrievals) {
    _result = pCopy(result);
    // std::cout << std::endl << "PolyMinorValue creator, " << pString(_result);
    _multiplications = multiplications;
    _summations = summations;
    _accumulatedMult = accumulatedMultiplications;
    _accumulatedSum = accumulatedSummations;
    _potentialRetrievals = potentialRetrievals;
    _retrievals = retrievals;
}

PolyMinorValue::PolyMinorValue () {
    _result = pISet(0);
    // std::cout << std::endl << "PolyMinorValue creator, " << pString(_result) << " STANDARD!";
    _multiplications = -1;
    _summations = -1;
    _accumulatedMult = -1;
    _accumulatedSum = -1;
    _potentialRetrievals = -1;
    _retrievals = -1;
}

PolyMinorValue::~PolyMinorValue()
{
  // p_Delete(&_result, currRing);
}

poly PolyMinorValue::getResult() const {
    return _result;
}

int PolyMinorValue::getWeight () const {
    // put measure for size of MinorValue here, i.e. number of monomials in polynomial;
    // so far, we use the accumulated number of multiplications (i.e., including all nested ones)
    // to simmulate the size of a polynomial
    return pLength(_result); // the number of monomials in the polynomial
}

string PolyMinorValue::toString () const {
    char h[10];

    // Let's see whether a cache has been used to compute this MinorValue:
    bool cacheHasBeenUsed = true;
    if (this->getRetrievals() == -1) cacheHasBeenUsed = false;

    string s = pString(_result);
    s += " [retrievals: ";
    if (cacheHasBeenUsed) { sprintf(h, "%ld", this->getRetrievals()); s += h; }
    else s += "/";
    s += " (of ";
    if (cacheHasBeenUsed) { sprintf(h, "%ld", this->getPotentialRetrievals()); s += h; }
    else s += "/";
    s += "), *: ";
    sprintf(h, "%ld", this->getMultiplications()); s += h;
    s += " (accumulated: ";
    sprintf(h, "%ld", this->getAccumulatedMultiplications()); s += h;
    s += "), +: ";
    sprintf(h, "%ld", this->getSummations()); s += h;
    s += " (accumulated: ";
    sprintf(h, "%ld", this->getAccumulatedSummations()); s += h;
    s += "), weight: ";
    sprintf(h, "%d", this->getWeight()); s += h;
    s += ", rank: ";
    if (cacheHasBeenUsed) { sprintf(h, "%d", this->getUtility()); s += h; }
    else s += "/";
    s += "]";
    return s;
}

PolyMinorValue::PolyMinorValue (const PolyMinorValue& mv) {
    _result = mv.getResult();
    _retrievals = mv.getRetrievals();
    _potentialRetrievals = mv.getPotentialRetrievals();
    _multiplications = mv.getMultiplications();
    _summations = mv.getSummations();
    _accumulatedMult = mv.getAccumulatedMultiplications();
    _accumulatedSum = mv.getAccumulatedSummations();
}