#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QElapsedTimer>


QString nextSeq(const QString &seq)
{
    QString temp;

    for(int i = 0; i < seq.size();)
    {
        int count = 1;

        int j = i + 1;
        while (j < seq.size())
        {
            if (seq.at(i) == seq.at(j))
            {
                ++count;
                ++j;
            }
            else
            {
                break;
            }
        }

        temp.push_back(QString::number(count));
        temp.push_back(seq.at(i));

        i = j;
    }

    return temp;
}

QString decimalToTernary(int n)
{
    // 10進数から3進数への変換。
    // Look and Say sequenceなので 0, 1, 2 のかわりに 1, 2, 3 で表現。

    if (n == 0)
        return QString::number(1);

    QString ternary;
    while (0 < n)
    {
        int r = n % 3;
        ternary.push_front(QString::number(r + 1));
        n /= 3;
    }
    return ternary;
}

void calcLookAndSay(const int init, const int maxseq)
{
    //
    QString seq = decimalToTernary(init);

    //
    QString fileNumber = QString("%1").arg(seq, 10, QLatin1Char('0'));
    QString fileName = "sequence" + fileNumber + ".txt";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);

    //
    out << seq << "\n";

    //
    QElapsedTimer timer;
    for (int i = 0; i < maxseq; ++i)
    {
        // maxseqが60を超えると終わる気配が無くなってくる。

        timer.start();
        seq = nextSeq(seq);
        out << seq << "\n";
        qDebug() << "loop" << i << "took" << timer.elapsed() << "msec.";
    }
}

int main(int argc, char *argv[])
{
    const int maxinit = 80; // 初期状態。3進数に変換される。
    const int maxseq = 20; // maxseq番目の数列まで数え上げる。

    for (int init = 0; init <= maxinit; ++init)
    {
        calcLookAndSay(init, maxseq);
        //qDebug() << decimalToTernary(init);
    }

    return 0;
}

