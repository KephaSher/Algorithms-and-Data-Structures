  while (l <= r) {
      int mid = (l + r) / 2;
      if (check(mid)) {
          ans = mid;
          l = mid + 1
      } else r = mid - 1;
  }
