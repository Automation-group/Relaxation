#ifndef RXBLOCK_H_
#define RXBLOCK_H_

#include <QObject>

#include <boost/function.hpp>

class RxBlock : public QObject
{
	Q_OBJECT
public:

	typedef boost::function<bool (void)> TerminateFunctor_t;

	/**
	 * @param prev Предыдущий блок
	 */
	explicit RxBlock(RxBlock* prev = 0)
		: m_next(0), m_isRunning(false), m_terminateFunc (falseConst)
	{
		if (prev)
			prev -> setNext(this);
	}

	RxBlock* next() const { return m_next;}

	void setTerminateFunctor(TerminateFunctor_t termFunctor)
	{
		m_terminateFunc = termFunctor;
	}

	static bool trueConst() { return true;}
	static bool falseConst() { return false;}

public Q_SLOTS:
	/**
	 * Запустить выполнение блока
	 */
	void start()
	{
		started();
		m_isRunning = true;
		run();
	}

Q_SIGNALS:
	void finished();
	void started();
	void terminated(const QString& message);
protected:
	bool isTerminate() const { return m_terminateFunc(); }
	bool isRunning() const { return m_isRunning; }
	/**
	 * Передать управление следующему блоку
	 */
	void doNext()
	{
		m_isRunning = false;
		finished();
		if (m_next) m_next->start();
	}
private:
	virtual void run() = 0;
	void setNext(RxBlock* next) { m_next = next; }
private:
	RxBlock* m_next;
	bool m_isRunning;
	TerminateFunctor_t m_terminateFunc;
};

#endif /*RXBLOCK_H_*/
