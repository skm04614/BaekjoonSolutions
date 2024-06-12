#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

inline void swap(ll& n, ll& m)
{
    ll tmp = n;
    n = m;
    m = tmp;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int sol = 0;

    ll x[2], y[2];
    ll xp[2], yp[2];
    std::cin >> x[0] >> y[0] >> x[1] >> y[1] >> xp[0] >> yp[0] >> xp[1] >> yp[1];

    if (x[0] > x[1])
    {
        swap(x[0], x[1]);
        swap(y[0], y[1]);
    }

    if (xp[0] > xp[1])
    {
        swap(xp[0], xp[1]);
        swap(yp[0], yp[1]);
    }

    ll dy = (y[1] - y[0]);
    ll dx = (x[1] - x[0]);

    ll dyp = (yp[1] - yp[0]);
    ll dxp = (xp[1] - xp[0]);

    if (dx == 0 && dxp == 0)
    {
        if (y[0] > y[1])
        {
            swap(x[0], x[1]);
            swap(y[0], y[1]);
        }

        if (yp[0] > yp[1])
        {
            swap(xp[0], xp[1]);
            swap(yp[0], yp[1]);
        }

        if (x[0] != xp[0])
        {
            sol = 0;
        }
        else if (y[0] < yp[0] && y[1] < yp[0])
        {
            sol = 0;
        }
        else if (y[0] > yp[1] && y[1] > yp[1])
        {
            sol = 0;
        }
        else if (yp[0] < y[0] && yp[1] < y[0])
        {
            sol = 0;
        }
        else if (yp[0] > y[1] && yp[1] > y[1])
        {
            sol = 0;
        }
        else
        {
            sol = 1;
        }
    }
    else if (dx == 0)
    {
        ll dxp_bp = dxp * yp[0] - dyp * xp[0];
        ll dxp_yp = dyp * x[0] + dxp_bp;
        bool is_negative = dxp < 0;

        ll y_lower = y[0] < y[1] ? y[0] : y[1];
        ll y_upper = y[0] > y[1] ? y[0] : y[1];

        if (xp[0] < x[0] && xp[1] < x[1])
        {
            sol = 0;
        }
        else if (xp[0] > x[0] && xp[1] > x[0])
        {
            sol = 0;
        }
        else if (!is_negative && y_lower * dxp <= dxp_yp && dxp_yp <= y_upper * dxp)
        {
            sol = 1;
        }
        else if (is_negative && y_lower * dxp >= dxp_yp && dxp_yp >= y_upper * dxp)
        {
            sol = 1;
        }
        else
        {
            sol = 0;
        }
    }
    else if (dxp == 0)
    {
        ll dx_b = dx * y[0] - dy * x[0];
        ll dx_y = dy * xp[0] + dx_b;
        bool is_negative = dx < 0;

        ll y_lower = yp[0] < yp[1] ? yp[0] : yp[1];
        ll y_upper = yp[0] > yp[1] ? yp[0] : yp[1];


        if (x[0] < xp[0] && x[1] < xp[1])
        {
            sol = 0;
        }
        else if (x[0] > xp[0] && x[1] > xp[0])
        {
            sol = 0;
        }
        else if (!is_negative && y_lower * dx <= dx_y && dx_y <= y_upper * dx)
        {
            sol = 1;
        }
        else if (is_negative && y_lower * dx >= dx_y && dx_y >= y_upper * dx)
        {
            sol = 1;
        }
        else
        {
            sol = 0;
        }
    }
    else
    {
        ll dx_b = dx * y[0] - dy * x[0];

        ll dxp_bp = dxp * yp[0] - dyp * xp[0];

        ll lhs_prefix = dy * dxp - dyp * dx;
        ll rhs = dx * dxp_bp - dxp * dx_b;

        bool is_negative = lhs_prefix < 0;

        if (dy * dxp == dyp * dx)
        {
            if (dx_b * dxp != dxp_bp * dx)
            {
                sol = 0;
            }
            else if (x[0] < xp[0] && x[1] < xp[0])
            {
                sol = 0;
            }
            else if (x[0] > xp[1] && x[1] > xp[1])
            {
                sol = 0;
            }
            else if (xp[0] < x[0] && xp[1] < x[0])
            {
                sol = 0;
            }
            else if (xp[0] > x[1] && xp[1] > x[1])
            {
                sol = 0;
            }
            else
            {
                sol = 1;
            }
        }
        else if (is_negative && lhs_prefix * x[0] >= rhs && rhs >= lhs_prefix * x[1]
            && lhs_prefix * xp[0] >= rhs && rhs >= lhs_prefix * xp[1])
        {
            sol = 1;
        }
        else if (!is_negative && lhs_prefix * x[0] <= rhs && rhs <= lhs_prefix * x[1]
            && lhs_prefix * xp[0] <= rhs && rhs <= lhs_prefix * xp[1])
        {
            sol = 1;
        }
        else
        {
            sol = 0;
        }
    }

    std::cout << sol;

    return 0;
}