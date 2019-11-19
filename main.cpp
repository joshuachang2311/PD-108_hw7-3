#include <iostream>

#include "dynamicarray.h"

constexpr unsigned int INVALID_INDEX = 10000000;

template <typename ElementType>
bool IsSubSetOf(dynamic_array<ElementType> consequent,
                dynamic_array<ElementType> antecedent);

int main() {
    unsigned int totalItems,
        totalTransactions,
        totalCaseItems,
        totalAntecedents = 0,
        totalNewItems = 0,
        finalIndex = INVALID_INDEX,
        finalOccurrences = 0;
    double supportThreshold;
    std::cin >> totalItems >> totalTransactions >> supportThreshold;
    dynamic_array<bool> visited(totalItems);
    dynamic_array<dynamic_array<unsigned int>> transactions(totalTransactions);
    for (unsigned int itemNumber = 0; itemNumber < totalItems; ++itemNumber) {
        visited[itemNumber] = false;
    }
    for (unsigned int transactionIndex = 0;
         transactionIndex < totalTransactions;
         ++transactionIndex) {
        unsigned int transactionSize;
        std::cin >> transactionSize;
        transactions[transactionIndex].set_size(transactionSize);
        for (unsigned int itemIndex = 0; itemIndex < transactionSize; ++itemIndex) {
            std::cin >> transactions[transactionIndex][itemIndex];
        }
    }
    std::cin >> totalCaseItems;
    dynamic_array<unsigned int> caseItems(totalCaseItems);
    for (unsigned int itemIndex = 0; itemIndex < totalCaseItems; ++itemIndex) {
        std::cin >> caseItems[itemIndex];
        visited[caseItems[itemIndex] - 1] = true;
    }

    for (unsigned int transactionIndex = 0;
         transactionIndex < transactions.size();
         ++transactionIndex) {
        if (IsSubSetOf(caseItems, transactions[transactionIndex])) {
            totalAntecedents += 1;
        }
    }
    dynamic_array<dynamic_array<unsigned int>> antecedents(totalAntecedents);
    unsigned int currentIndex = 0;
    for (unsigned int transactionIndex = 0;
         transactionIndex < transactions.size();
         ++transactionIndex) {
        if (IsSubSetOf(caseItems, transactions[transactionIndex])) {
            antecedents[currentIndex] =
                dynamic_array<unsigned int>(transactions[transactionIndex]);
            currentIndex += 1;
            if (currentIndex >= antecedents.size()) {
                break;
            }
        }
    }

    for (unsigned int antecedentIndex = 0;
         antecedentIndex < antecedents.size();
         ++antecedentIndex) {
        for (unsigned int itemIndex = 0;
             itemIndex < antecedents[antecedentIndex].size();
             ++itemIndex) {
            if (!visited[antecedents[antecedentIndex][itemIndex] - 1]) {
                totalNewItems += 1;
                visited[antecedents[antecedentIndex][itemIndex] - 1] = true;
            }
        }
    }
    dynamic_array<unsigned int> newItems(totalNewItems);
    for (unsigned int itemNumber = 0; itemNumber < totalItems; ++itemNumber) {
        visited[itemNumber] = false;
    }
    for (unsigned int itemIndex = 0; itemIndex < totalCaseItems; ++itemIndex) {
        visited[caseItems[itemIndex] - 1] = true;
    }
    currentIndex = 0;
    for (unsigned int antecedentIndex = 0;
         antecedentIndex < antecedents.size();
         ++antecedentIndex) {
        bool shouldBreak = false;
        for (unsigned int itemIndex = 0;
             itemIndex < antecedents[antecedentIndex].size();
             ++itemIndex) {
            if (!visited[antecedents[antecedentIndex][itemIndex] - 1]) {
                newItems[currentIndex] = antecedents[antecedentIndex][itemIndex];
                visited[antecedents[antecedentIndex][itemIndex] - 1] = true;
                currentIndex += 1;
                if (currentIndex >= totalNewItems) {
                    shouldBreak = true;
                    break;
                }
            }
        }
        if (shouldBreak) {
            break;
        }
    }

    for (unsigned int newItemIndex = 0; newItemIndex < newItems.size(); ++newItemIndex) {
        unsigned int occurrences = 0;
        for (unsigned int antecedentIndex = 0; antecedentIndex < antecedents.size(); ++antecedentIndex) {
            if (antecedents[antecedentIndex].binary_search_contains(newItems[newItemIndex])) {
                occurrences += 1;
            }
        }
        if (1.0 * occurrences / totalTransactions >= supportThreshold) {
            if (occurrences > finalOccurrences) {
                finalIndex = newItems[newItemIndex];
                finalOccurrences = occurrences;
            }
        }
    }

    if (finalIndex != INVALID_INDEX) {
        std::cout << finalIndex << "," << finalOccurrences << "," << totalAntecedents;
    }

    return 0;
}

template <typename ElementType>
bool IsSubSetOf(dynamic_array<ElementType> consequent,
                dynamic_array<ElementType> antecedent) {
    unsigned int currentIndex = 0;
    for (unsigned int itemIndex = 0; itemIndex < antecedent.size(); ++itemIndex) {
        if (consequent[currentIndex] == antecedent[itemIndex]) {
            currentIndex += 1;
            if (currentIndex >= consequent.size()) {
                return true;
            }
        }
    }
    return false;
}