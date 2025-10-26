#!/bin/bash

./PMergeMe 21 1 13 2 17 3 12 4 20 5 15 6 19 7 14 8 18 9 16 10 11

python3 -c "import random; print(' '.join(str(random.randint(1, 100)) for _ in range(100)))" | xargs ./PMergeMe

python3 -c "import random; print(' '.join(str(random.randint(1, 200)) for _ in range(200)))" | xargs ./PMergeMe

python3 -c "import random; print(' '.join(str(random.randint(1, 500)) for _ in range(500)))" | xargs ./PMergeMe

python3 -c "import random; print(' '.join(str(random.randint(1, 1000)) for _ in range(1000)))" | xargs ./PMergeMe

python3 -c "import random; print(' '.join(str(random.randint(1, 3000)) for _ in range(3000)))" | xargs ./PMergeMe
